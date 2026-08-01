#include "rcc_driver.h"

// AHB1 GPIO Clock Enable Function //
void gpio_clock_enable(ahb1_clock_port_t port, rcc_status_t clock_status){
    switch (clock_status) {
        case ON: 
            RCC->RCC_AHB1ENR |= ((1UL) << (port));
            break;

        case OFF: 
            RCC->RCC_AHB1ENR &= ~((1UL) << (port));
            break;

        default: 
            RCC->RCC_AHB1ENR &= ~((1UL) << (port));
    }
}