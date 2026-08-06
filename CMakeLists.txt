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
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/stm32f446xe_flash.ld)
set(STARTUP_ASM   ${CMAKE_SOURCE_DIR}/startup/startup_stm32f446xx.S)

# ---------------------------------------------------------------------------
# HAL library — grows as you add peripherals
# ---------------------------------------------------------------------------
add_library(stm32_hal STATIC
    drivers/src/gpio_driver.c
    drivers/src/rcc_driver.c
)
target_include_directories(stm32_hal PUBLIC drivers/inc)

function(add_example name)
    add_executable(${name}
        examples/${name}/main.c
        startup/system_stm32f446.c
        ${STARTUP_ASM}
    )
    target_link_libraries(${name} PRIVATE stm32_hal)
    target_link_options(${name} PRIVATE
        -T${LINKER_SCRIPT}
        -Wl,-Map=${CMAKE_BINARY_DIR}/${name}.map,--cref
        -Wl,--print-memory-usage
    )
    set_target_properties(${name} PROPERTIES
        SUFFIX ".elf"
        LINK_DEPENDS ${LINKER_SCRIPT}
    )
    add_custom_command(TARGET ${name} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${name}> ${name}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${name}> ${name}.hex
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${name}>
    )
    add_custom_target(flash_${name}
        COMMAND openocd -f board/st_nucleo_f4.cfg
                -c "program $<TARGET_FILE:${name}> verify reset exit"
        USES_TERMINAL
    )
    add_dependencies(flash_${name} ${name})
endfunction()

add_example(blink)