#pragma once

#include "umdr/display/graphics_rgb565.h"
#include <umdr/comm/can/input_system.h>
#include <umdr/comm/can/output_system.h>

#include <FreeRTOS.h>
#include <cmsis_os2.h>

enum cassandra_tool_state : uint16_t
{
    CASSANDRA_TOOL_SELECTION = 0,
    CASSANDRA_TOOL_FS_PROBE  = 1,
    CASSANDRA_TOOL_SWD_PROBE = 2,
};

struct CASSANDRA_tool
{
    struct UMDR_graphics_rgb565 * graphics;
};
