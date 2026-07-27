/**
 * @file gpio_driver.c
 * @author Dominick Green (greendom99@gmail.com)
 * @brief GPIO driver implementation for STM32 microcontrollers.
 * @version 0.1
 * @date 2026-07-26
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdint.h>
#include <stddef.h>
#include "gpio_driver.h" 

void set_pin_mode(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_mode_t mode){
    gpio_port->MODER &= ~(0x03 << (pin * 2)); // Clear the mode bits for the specified pin
    gpio_port->MODER |= (mode << (pin * 2)); // Set the new mode for the specified pin
}

void set_pin_output_type(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_output_type_t output_type){
    gpio_port->OTYPER &= ~(0x01 << pin); // Clear the output type bit for the specified pin
    gpio_port->OTYPER |= (output_type << pin); // Set the new output type for the specified pin
}

void set_pin_speed(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_speed_t speed){
    gpio_port->OSPEEDR &= ~(0x03 << (pin * 2)); // Clear the speed bits for the specified pin
    gpio_port->OSPEEDR |= (speed << (pin * 2)); // Set the new speed for the specified pin
}

void set_pin_pull(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_pull_t pull){
    gpio_port->PUPDR &= ~(0x03 << (pin * 2)); // Clear the pull-up/pull-down bits for the specified pin
    gpio_port->PUPDR |= (pull << (pin * 2)); // Set the new pull-up/pull-down configuration for the specified pin
}

void set_pin_alternate_function(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function_t af){
    if(pin < 8){
        gpio_port->AFRL &= ~(0x0F << (pin * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRL |= (af << (pin * 4)); // Set the new alternate function for the specified pin
    } else {
        gpio_port->AFRH &= ~(0x0F << ((pin - 8) * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRH |= (af << ((pin - 8) * 4)); // Set the new alternate function for the specified pin
    }
}

void set_pin_state(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_set_reset_t set_reset){
    if(set_reset == SET){
        gpio_port->BSRR = (1UL << pin); // Set the set bit for the specified pin
    } else{
        gpio_port->BSRR = (1UL << (pin + 16)); // Set the reset bit for the specified pin
    }
}

void set_clock_state(clock_status_t clock_state){
    //to do//
    switch(clock_state){
        case ON:
            (RCC) |= (1U); 
            break;
        case OFF: 
            (RCC) &= ~(1U);
            break;
        default:
            (RCC) &= ~(1U);        
    }
}

GPIO_status_t gpio_init(GPIO_t *gpio_port, const GPIO_config_t *config){

    //Error checking//
    if ((gpio_port == NULL)||(config == NULL)){return GPIO_ERROR_INVALID_PIN;}
    if (config->pin_mask == 0U){return GPIO_ERROR_INVALID_PIN;}

    //port init loop//
    for(uint8_t pin = 0; pin < 16; pin++){
        //Pin mask check to speed up loop//
        if((config->pin_mask & (1U << pin)) == 0U) {continue;}
        //otherwise  init pin//
        set_pin_output_type(gpio_port, pin, config->output_type);
        set_pin_speed(gpio_port, pin, config->speed);
        set_pin_pull(gpio_port, pin, config->pull);
        set_pin_alternate_function(gpio_port, pin, config->alternate_function);
        set_pin_state(gpio_port, pin, config->pin_state);
        set_pin_mode(gpio_port, pin, config->mode);
    }

    return(GPIO_SUCCESS);
}

