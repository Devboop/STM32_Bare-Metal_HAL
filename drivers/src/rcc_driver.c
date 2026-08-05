/** @file rcc_driver.c
 *  @brief RCC driver implementation
 *  @author Dominick Green 
 */

#include "../inc/rcc_driver.h"

// AHB1 GPIO Clock Enable Function //
void rcc_ahb1_clock_enable(ahb1_clock_port_t port, rcc_status_t clock_status){
    switch (clock_status) {
        case RCC_CLK_ON: 
            RCC->AHB1ENR |= ((1UL) << (port));
            break;

        case RCC_CLK_OFF: 
            RCC->AHB1ENR &= ~((1UL) << (port));
            break;

        default: 
            RCC->AHB1ENR &= ~((1UL) << (port));
    }
}