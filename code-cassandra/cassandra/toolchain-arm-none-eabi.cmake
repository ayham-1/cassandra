set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)


# Prevent CMake from trying to run test binaries
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Optional: specify flags (tune to your MCU)
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp")

set(CMAKE_C_FLAGS_INIT   "${CPU_FLAGS} -ffreestanding -fno-builtin")
set(CMAKE_CXX_FLAGS_INIT "${CPU_FLAGS} -ffreestanding -fno-builtin")
