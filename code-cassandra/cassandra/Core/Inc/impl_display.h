#pragma once

#include <stdint.h>

bool
umdr_display_driver_ssd1353_send_command(uint8_t byte);

bool
umdr_display_driver_ssd1353_send_single_data(uint8_t data);

bool
umdr_display_driver_ssd1353_send_data(volatile uint8_t * data, size_t y_offset, size_t sz);
