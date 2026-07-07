cmake_minimum_required(VERSION 3.15)
project(LEDFirmware C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(led_test
    tests/led_test.c
)

target_include_directories(led_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(firmware.elf
    src/main.c
    src/led.c
)

target_compile_options(firmware.elf PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -ffreestanding
)

target_link_options(firmware.elf PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -nostdlib
    -nostartfiles
    -Wl,--gc-sections
)

find_program(OBJCOPY NAMES arm-none-eabi-objcopy REQUIRED)

add_custom_command(
    TARGET firmware.elf
    POST_BUILD
    COMMAND ${OBJCOPY} -O ihex $<TARGET_FILE:firmware.elf> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/firmware.hex
    COMMAND ${OBJCOPY} -O binary $<TARGET_FILE:firmware.elf> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/firmware.bin
    COMMENT "Generating HEX and BIN"
)
