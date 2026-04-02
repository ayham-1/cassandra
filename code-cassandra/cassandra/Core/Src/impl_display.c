#include "main.h"
#include "state.h"

#include "spi.h"

#include <umdr/hal.h>

bool
umdr_display_driver_ssd1353_send_command(uint8_t byte)
{
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, GPIO_PIN_RESET);
    return HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY) == HAL_OK;
}

bool
umdr_display_driver_ssd1353_send_single_data(uint8_t data)
{
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, GPIO_PIN_SET);
    return HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY) == HAL_OK;
}

bool
umdr_display_driver_ssd1353_send_data(volatile uint8_t * data, size_t y_offset, size_t sz)
{
	umdr_display_driver_ssd1353_window(&state.display_driver, 0, state.display_driver.driver.framebuffer0.pixel_width - 1, y_offset, y_offset + state.display_driver.driver.framebuffer0.pixel_height - 1);

	HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, GPIO_PIN_SET);
    return HAL_SPI_Transmit_DMA(&hspi1, (void *)data, sz) == HAL_OK;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * hspi)
{
	umdr_display_driver_data_write_completed(&state.display_driver.driver);
}
