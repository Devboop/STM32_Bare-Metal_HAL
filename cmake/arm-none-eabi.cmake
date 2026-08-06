# ---------------------------------------------------------------------------
# Cross-compilation toolchain for ARM Cortex-M4 (STM32F446RE)
# Usage: cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
# ---------------------------------------------------------------------------

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# CMake normally test-compiles a full executable to validate the compiler.
# That fails here because a full link needs the linker script, which isn't
# wired up yet at configure time. Building a static library instead is enough
# to prove the compiler works.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY      arm-none-eabi-objcopy CACHE FILEPATH "objcopy")
set(CMAKE_SIZE         arm-none-eabi-size    CACHE FILEPATH "size")

# Cortex-M4F. -mfloat-abi=hard must match across every object in the build.
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_FLAGS_INIT   "${CPU_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS_INIT "${CPU_FLAGS} -x assembler-with-cpp")

# -nostdlib: no libc, no libgcc, no crt0.
# Required here — the linker script's /DISCARD/ block throws those libraries
# away anyway, so linking them would only produce confusing errors.
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CPU_FLAGS} -nostdlib -Wl,--gc-sections")

# Look for programs on the host, but headers/libraries only in the sysroot.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
