cmake_minimum_required(VERSION 3.16)

project(bert LANGUAGES C CXX)

# ──────────────────────────────────────────────
# Project settings
# ──────────────────────────────────────────────
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXPORT_COMPILE_COMMANDS ON)

set(HEADER_DIR "${CMAKE_CURRENT_LIST_DIR}/Core/Inc")

file(GLOB_RECURSE BERT_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/Core/Src/*.c)

set(HAL_DIR "${PROJECT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver")
set(CMSIS_DIR "${PROJECT_SOURCE_DIR}/Drivers/CMSIS")
set(FREERTOS_DIR "${PROJECT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS")

# i know this bad practice, but STM32CubeIDE forces a workspace-way of project
# architecture, and therefore <project_name>'s code does not work outside of a 
# valid workspace that has libumdr too
set(LIBUMDR_DIR "${PROJECT_SOURCE_DIR}/../libumdr/")

# Collect HAL sources
file(GLOB_RECURSE HAL_SOURCES
    ${HAL_DIR}/Src/*.c
)

# Collect FreeRTOS sources
file(GLOB_RECURSE FREERTOS_SOURCES
    ${FREERTOS_DIR}/*/*.c
)

# Collect libumdr sources
file(GLOB_RECURSE LIBUMDR_SOURCES
    ${LIBUMDR_DIR}/Src/src/*.c
)

add_executable(bert
    ${BERT_SOURCES}
    ${HAL_SOURCES}
    ${FREERTOS_SOURCES}
    ${LIBUMDR_SOURCES}
)

target_include_directories(bert PUBLIC
    ${HEADER_DIR}
    ${HAL_DIR}/Inc
    ${HAL_DIR}/Inc/Legacy
    ${CMSIS_DIR}/Include
    ${CMSIS_DIR}/Device/ST/STM32F4xx/Include
    ${FREERTOS_DIR}/Source/include
    ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM4F
    ${FREERTOS_DIR}/Source/CMSIS_RTOS_V2/
    ${LIBUMDR_DIR}/Inc
    ${PROJECT_SOURCE_DIR}/USB_DEVICE/App/
    ${PROJECT_SOURCE_DIR}/USB_DEVICE/Target/
    ${PROJECT_SOURCE_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
)

target_compile_definitions(bert PUBLIC STM32F446xx USE_HAL_DRIVER USE_FREERTOS)
target_compile_options(bert PRIVATE
    -Wall -Wextra -Wpedantic -Werror
    -Wno-unused-function -Wno-pedantic -Wno-unused-parameter
)
