#pragma once

#include <stdint.h>

#include <umdr/hal.h>

#include <umdr/display/drivers/ssd1353.h>
#include <umdr/display/graphics_rgb565.h>

enum cassandra_pcb_config : uint32_t
{
    cassandra_pcb_display_width  = 160,
    cassandra_pcb_display_height = 128,
    cassandra_pcb_display_fps    = 15,


	cassandra_pcb_display_partial = true,
	cassandra_pcb_display_tiles = 4,
};

struct cassandra_pcb_state
{
    volatile uint16_t framebuffer0[cassandra_pcb_display_height / cassandra_pcb_display_tiles][cassandra_pcb_display_width];
    volatile uint16_t framebuffer1[cassandra_pcb_display_height / cassandra_pcb_display_tiles][cassandra_pcb_display_width];

    struct UMDR_display_driver_ssd1353 display_driver;
    struct UMDR_graphics_rgb565 graphics;
};

void
cassandra_pcb_init(void);

extern struct cassandra_pcb_state state;
