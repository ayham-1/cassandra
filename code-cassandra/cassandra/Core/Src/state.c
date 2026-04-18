#include "state.h"

#include "can.h"

#include "impl_display.h"
#include "umdr/display/colors.h"
#include "umdr/display/drivers/driver.h"

#include <umdr/display/fonts/ibm_plex_mono_22pt.h>
#include <umdr/display/fonts/ibm_plex_mono_75pt.h>

#include <string.h>

struct cassandra_pcb_state state = {

    .graphics =
        (struct UMDR_graphics_paletted){
            .big_num =
                (struct UMDR_font){
                    .point_size  = 75,
                    .spacing     = 3,
                    .blank_width = 5,
                    .scale       = 1,
                    .heights     = ibm_plex_mono_75pt_heights,
                    .widths      = ibm_plex_mono_75pt_widths,
                    .glyphs      = ibm_plex_mono_75pt_glyphs,
                },
            .big =
                (struct UMDR_font){
                    .point_size  = 66,
                    .spacing     = 3,
                    .blank_width = 15,
                    .scale       = 3,
                    .heights     = ibm_plex_mono_22pt_heights,
                    .widths      = ibm_plex_mono_22pt_widths,
                    .glyphs      = ibm_plex_mono_22pt_glyphs,
                },

            .medium =
                (struct UMDR_font){
                    .point_size  = 44,
                    .spacing     = 5,
                    .blank_width = 10,
                    .scale       = 2,
                    .heights     = ibm_plex_mono_22pt_heights,
                    .widths      = ibm_plex_mono_22pt_widths,
                    .glyphs      = ibm_plex_mono_22pt_glyphs,
                },

            .small =
                (struct UMDR_font){
                    .point_size  = 22,
                    .spacing     = 5,
                    .blank_width = 7,
                    .scale       = 1,
                    .heights     = ibm_plex_mono_22pt_heights,
                    .widths      = ibm_plex_mono_22pt_widths,
                    .glyphs      = ibm_plex_mono_22pt_glyphs,
                },
        },
};

void
cassandra_pcb_init(void)
{
    state.can_in_filters[0] = (CAN_FilterTypeDef){
        .FilterBank           = 0,
        .FilterMode           = CAN_FILTERMODE_IDMASK,
        .FilterScale          = CAN_FILTERSCALE_32BIT,
        .FilterIdHigh         = 0x0,
        .FilterIdLow          = 0x0,
        .FilterMaskIdHigh     = 0x0,
        .FilterMaskIdLow      = 0x0,
        .FilterFIFOAssignment = CAN_RX_FIFO0,
        .FilterActivation     = ENABLE,
        .SlaveStartFilterBank = 0,
    };
    state.can_ins[0] = (struct UMDR_CanInputSysEntry){
        .frames = xQueueCreate(45, sizeof(struct UMDR_CanFrame)),
        .canid  = 0,
    };
    state.hcan_ext  = &hcan2;
    state.can_input = (struct UMDR_CanInputSys){
        .name = "can_output",
        .hcan = state.hcan_ext,

        .count              = cassandra_pcb_can_in_entries_cnt,
        .entries            = &state.can_ins[0],
        .filters            = &state.can_in_filters[0],
        .filter_count       = cassandra_pcb_can_in_filters_cnt,
        .queue_wait_time_ms = 10,
        .queue_length       = 45,
    };

    umdr_caninput_init(&state.can_input);

    if (HAL_CAN_Start(&hcan2) != HAL_OK)
        Error_Handler();

    if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
        Error_Handler();
    if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
        Error_Handler();
    if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
        Error_Handler();

    state.display_driver.driver.framebuffer0 = (struct UMDR_display_driver_fb){
        .ptr          = (void *)&state.framebuffer0[0][0],
        .format       = UMDR_display_driver_fb_palette,
        .byte_size    = sizeof(state.framebuffer0),
        .pixel_width  = cassandra_pcb_display_width,
        .pixel_height = cassandra_pcb_display_height,
    };

    state.display_driver.driver.framebuffer1 = (struct UMDR_display_driver_fb){
        .ptr          = (void *)&state.framebuffer1[0][0],
        .format       = UMDR_display_driver_fb_palette,
        .byte_size    = sizeof(state.framebuffer1),
        .pixel_width  = cassandra_pcb_display_width,
        .pixel_height = cassandra_pcb_display_height,

    };

    state.display_driver.contrast.master = 0xC7;
    state.display_driver.contrast.a      = 0xC0;
    state.display_driver.contrast.b      = 0x80;
    state.display_driver.contrast.c      = 0xC0;

    state.display_driver.driver.send_command     = &umdr_display_driver_ssd1353_send_command;
    state.display_driver.driver.send_single_data = &umdr_display_driver_ssd1353_send_single_data;
    state.display_driver.driver.send_data        = &umdr_display_driver_ssd1353_send_data;
    state.display_driver.driver.draw_framebuffer = &state.display_driver.driver.framebuffer0;

    state.display_driver.driver.height = cassandra_pcb_display_height;
    state.display_driver.driver.width  = cassandra_pcb_display_width;
    state.display_driver.driver.fps    = cassandra_pcb_display_fps;

    state.display_driver.driver.partial.enable     = cassandra_pcb_display_partial;
    state.display_driver.driver.partial.tile_count = cassandra_pcb_display_tiles;
    state.display_driver.driver.partial.writing    = xSemaphoreCreateBinary();

    state.display_driver.driver.paletting.enable          = cassandra_pcb_display_paletting;
    state.display_driver.driver.paletting.map_fn          = &umdr_palette_marita_to_rgb565_map;
    state.display_driver.driver.paletting.unpacked_buffer = (struct UMDR_display_driver_fb){
        .ptr          = (void *)&state.unpacked_framebuffer[0][0],
        .format       = UMDR_display_driver_fb_rgb565,
        .byte_size    = sizeof(state.unpacked_framebuffer),
        .pixel_width  = cassandra_pcb_display_width,
        .pixel_height = cassandra_pcb_display_height / cassandra_pcb_display_tiles,
    };
    state.display_driver.driver.paletting.unpacked_buffer_tile_count = cassandra_pcb_display_tiles;
    state.display_driver.driver.paletting.writing                    = xSemaphoreCreateBinary();
    state.display_driver.driver.paletting.unpack_fn                  = &umdr_display_driver_unpack_8bit_to_16bit;

    umdr_display_driver_assert_validity(&state.display_driver.driver);
    umdr_display_driver_ssd1353_init(&state.display_driver);
    umdr_display_driver_data_write_completed(&state.display_driver.driver);

    state.graphics.display_driver = &state.display_driver.driver;

    const char * texts[] = {
        "TESTS",
    };

    const struct UMDR_graphics_point text1_point = {
        .x = 0,
        .y = 0,
    };

    const struct UMDR_graphics_point point1 = {
        .x = 0,
        .y = 0,
    };
    const struct UMDR_graphics_point point2 = {
        .x = cassandra_pcb_display_width,
        .y = cassandra_pcb_display_height,
    };

    const struct UMDR_graphics_point point3 = {
        .x = cassandra_pcb_display_width,
        .y = 0,
    };
    const struct UMDR_graphics_point point4 = {
        .x = 0,
        .y = cassandra_pcb_display_height,
    };

    const struct UMDR_graphics_point point5 = {
        .x = 0,
        .y = cassandra_pcb_display_height / 2,
    };
    const struct UMDR_graphics_point point6 = {
        .x = cassandra_pcb_display_width,
        .y = cassandra_pcb_display_height / 2,
    };

    while (1)
    {
        umdr_graphics_paletted_clear_framebuffer(&state.graphics, (enum UMDR_display_palette_generic)UMDR_color_blue);
        umdr_graphics_paletted_draw_medium_text(&state.graphics,
                                                (enum UMDR_display_palette_generic)UMDR_color_orange,
                                                text1_point,
                                                texts[0],
                                                strlen(texts[0]));

        umdr_graphics_paletted_draw_line(
            &state.graphics, (enum UMDR_display_palette_generic)UMDR_color_blue, point1, point2);
        umdr_graphics_paletted_draw_line(
            &state.graphics, (enum UMDR_display_palette_generic)UMDR_color_green, point3, point4);

        umdr_graphics_paletted_draw_line(
            &state.graphics, (enum UMDR_display_palette_generic)UMDR_color_red, point5, point6);

        umdr_display_driver_commit(state.graphics.display_driver);
        umdr_display_driver_wait_till_writable(state.graphics.display_driver);
    }
}
