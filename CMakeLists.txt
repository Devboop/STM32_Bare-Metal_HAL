cmake_minimum_required(VERSION 3.16)
project(stm32_bare_metal_hal
    LANGUAGES C ASM
    DESCRIPTION "Bare-metal peripheral driver library for STM32F446RE"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)          # strict c11, not gnu11

# Warnings on C only — passing -Wpedantic to the assembler is noise.
add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Wpedantic>
)

# ---------------------------------------------------------------------------
# Paths — check these against your actual filenames. CubeMX names things like
# STM32F446RETX_FLASH.ld and startup_stm32f446retx.s
# ---------------------------------------------------------------------------
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/stm32f446re.ld)
set(STARTUP_ASM   ${CMAKE_SOURCE_DIR}/startup/startup_stm32f446.s)

# ---------------------------------------------------------------------------
# HAL library — grows as you add peripherals
# ---------------------------------------------------------------------------
add_library(stm32_hal STATIC
    src/gpio_driver.c
    src/rcc_driver.c
)
target_include_directories(stm32_hal PUBLIC include)

# ---------------------------------------------------------------------------
# blink example
# ---------------------------------------------------------------------------
add_executable(blink
    examples/blink/main.c
    startup/system_stm32f446.c       # SystemInit + __libc_init_array stubs
    ${STARTUP_ASM}
)

target_link_libraries(blink PRIVATE stm32_hal)

target_link_options(blink PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_BINARY_DIR}/blink.map,--cref
    -Wl,--print-memory-usage
)

set_target_properties(blink PROPERTIES
    SUFFIX ".elf"
    LINK_DEPENDS ${LINKER_SCRIPT}    # relink when the script changes
)

add_custom_command(TARGET blink POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:blink> blink.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:blink> blink.hex
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:blink>
    COMMENT "Generating blink.bin / blink.hex"
)

# ---------------------------------------------------------------------------
# Convenience: cmake --build build --target flash
# ---------------------------------------------------------------------------
add_custom_target(flash
    COMMAND openocd -f board/st_nucleo_f4.cfg
            -c "program $<TARGET_FILE:blink> verify reset exit"
    USES_TERMINAL
    COMMENT "Flashing via ST-LINK"
)
add_dependencies(flash blink)
