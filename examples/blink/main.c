/**
 * @file main.c
 * @author Dominick Green
 * @brief Main function for LED blinking example
 * @version 0.1
 * @date 2024-06-05
 */

#include "gpio_driver.h"
#include "rcc_driver.h"

int main(void){

    // TO DO: Declare and initialize pin configuration structure //
    GPIO_config_t led_pin_config = {
        .pin_mask = (1 << 5),
        .mode = OUTPUT,
        .output_type = PUSH_PULL,
        .speed = HIGH,
        .pull = NO_PULL,
        .alternate_function = AF0,
        .pin_state = RESET
    };

    // TO DO: Turn on clock for GPIO port //
    rcc_ahb1_clock_enable(RCC_AHB1_GPIOA, RCC_CLK_ON);

    // TO DO: Call GPIO initialization function //
    gpio_init(GPIOA, &led_pin_config);

    // TO DO: LED Blinking function //
    while(1) {
        set_pin_state(GPIOA, 5, SET);
        for (volatile int i = 0; i < 100000; i++); 

        set_pin_state(GPIOA, 5, RESET);
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
    }
