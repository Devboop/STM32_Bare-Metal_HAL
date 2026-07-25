#include <stdint.h>
#include "gpio_driver.h" 

//Set GPIO pin mode function definition //
void set_pin_mode(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_mode mode){
    gpio_port->MODER &= ~(0x03 << (pin * 2)); // Clear the mode bits for the specified pin
    gpio_port->MODER |= (mode << (pin * 2)); // Set the new mode for the specified pin
}

void set_pin_output_type(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_output_type output_type){
    gpio_port->OTYPER &= ~(0x01 << pin); // Clear the output type bit for the specified pin
    gpio_port->OTYPER |= (output_type << pin); // Set the new output type for the specified pin
}

void set_pin_speed(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_speed speed){
    gpio_port->OSPEEDR &= ~(0x03 << (pin * 2)); // Clear the speed bits for the specified pin
    gpio_port->OSPEEDR |= (speed << (pin * 2)); // Set the new speed for the specified pin
}

void set_pin_pull(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_pull pull){
    gpio_port->PUPDR &= ~(0x03 << (pin * 2)); // Clear the pull-up/pull-down bits for the specified pin
    gpio_port->PUPDR |= (pull << (pin * 2)); // Set the new pull-up/pull-down configuration for the specified pin
}

void set_pin_alternate_function(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function af){
    if(pin < 8){
        gpio_port->AFRL &= ~(0x0F << (pin * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRL |= (af << (pin * 4)); // Set the new alternate function for the specified pin
    } else {
        gpio_port->AFRH &= ~(0x0F << ((pin - 8) * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRH |= (af << ((pin - 8) * 4)); // Set the new alternate function for the specified pin
    }
}

void bit_set_reset(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_set_reset set_reset){
    if(set_reset == SET){
        gpio_port->BSRR = (1UL << pin); // Set the set bit for the specified pin
    } else{
        gpio_port->BSRR = (1UL << (pin + 16)); // Set the reset bit for the specified pin
    }
}

// Toggle GPIO pin with a short delay WIP//
void toggle_pin_with_delay(GPIO_t *gpio_port, uint8_t pin, uint32_t delay){
    while(1){
        bit_set_reset(gpio_port, pin, SET); // Set the pin
        for(volatile uint32_t i = 0; i < delay; i++); // Delay
        bit_set_reset(gpio_port, pin, RESET); // Reset the pin
        for(volatile uint32_t i = 0; i < delay; i++); // Delay
    }
}

//single timed blink function WIP//
void timed_blink(GPIO_t *gpio_port, uint8_t pin, uint32_t delay) {
    if (gpio_port->ODR & (1 << pin)){
        bit_set_reset(gpio_port, pin, RESET); 
        for (volatile uint32_t i = 0; i < delay; i++); //Fixed Delay
        bit_set_reset(gpio_port, pin, SET);
    }
}    

