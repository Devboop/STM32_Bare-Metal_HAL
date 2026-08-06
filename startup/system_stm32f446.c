/*
 * Minimal replacements for the two symbols ST's startup_stm32f446.s calls
 * but does not define. Normally these come from system_stm32f4xx.c and libc;
 * this project links neither.
 */

#include <stdint.h>

/* SCB->CPACR, Cortex-M4 coprocessor access control */
#define SCB_CPACR (*(volatile uint32_t *)0xE000ED88UL)

void SystemInit(void);
void __libc_init_array(void);

/*
 * Called from Reset_Handler before .data/.bss init, so it must not touch any
 * globals. Enabling the FPU here is mandatory: the build uses
 * -mfloat-abi=hard, and the first floating-point instruction raises a
 * UsageFault if CP10/CP11 aren't granted full access first.
 *
 * The chip stays on HSI at 16 MHz — clock tree setup belongs in your RCC
 * driver, not here.
 */
void SystemInit(void)
{
    SCB_CPACR |= (0xFUL << 20);   /* CP10 and CP11, full access */
    __asm volatile ("dsb");
    __asm volatile ("isb");
}

/*
 * Runs static constructors from .init_array. The real implementation lives in
 * libc, which this project discards. C has no static constructors, so
 * .init_array is empty and a no-op is exactly equivalent.
 *
 * If you ever link C++ or add __attribute__((constructor)) functions, this
 * stub silently skips them — that's the moment to switch to real libc.
 */
void __libc_init_array(void)
{
}
