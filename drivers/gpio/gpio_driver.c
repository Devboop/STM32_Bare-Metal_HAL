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

void set_pin_mode(uint32_t gpio_reg, uint8_t pin, GPIO_pin_mode_t mode){
    gpio_reg &= ~(0x03 << (pin * 2)); // Clear the mode bits for the specified pin
    gpio_reg |= (mode << (pin * 2)); // Set the new mode for the specified pin
}

void set_pin_output_type(uint32_t gpio_reg, uint8_t pin, GPIO_pin_output_type_t output_type){
    gpio_reg &= ~(0x01 << pin); // Clear the output type bit for the specified pin
    gpio_reg |= (output_type << pin); // Set the new output type for the specified pin
}

void set_pin_speed(uint32_t gpio_reg, uint8_t pin, GPIO_pin_speed_t speed){
    gpio_reg &= ~(0x03 << (pin * 2)); // Clear the speed bits for the specified pin
    gpio_reg |= (speed << (pin * 2)); // Set the new speed for the specified pin
}

void set_pin_pull(uint32_t gpio_reg, uint8_t pin, GPIO_pin_pull_t pull){
    gpio_reg &= ~(0x03 << (pin * 2)); // Clear the pull-up/pull-down bits for the specified pin
    gpio_reg |= (pull << (pin * 2)); // Set the new pull-up/pull-down configuration for the specified pin
}

void set_pin_alternate_function(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function_t af){
    if(pin < 8){
        ((GPIO_t *)gpio_port)->AFRL &= ~(0x0F << (pin * 4)); // Clear the alternate function bits for the specified pin
        ((GPIO_t *)gpio_port)->AFRL |= (af << (pin * 4)); // Set the new alternate function for the specified pin
    } else {
        ((GPIO_t *)gpio_port)->AFRH &= ~(0x0F << ((pin - 8) * 4)); // Clear the alternate function bits for the specified pin
        ((GPIO_t *)gpio_port)->AFRH |= (af << ((pin - 8) * 4)); // Set the new alternate function for the specified pin
    }
}

void set_pin_state(uint32_t gpio_reg, uint8_t pin, GPIO_pin_set_reset_t set_reset){
    if(set_reset == SET){
        gpio_reg = (1UL << pin); // Set the set bit for the specified pin
    } else{
        gpio_reg = (1UL << (pin + 16)); // Set the reset bit for the specified pin
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
    if ((gpio_port == NULL)||(config->pin_mask == 0U)){return GPIO_ERROR_INVALID_PIN;}

    //Declare local register variables for mutation in loop//
    uint32_t mode_reg = gpio_port->MODER;
    uint32_t otype_reg = gpio_port->OTYPER;
    uint32_t speed_reg = gpio_port->OSPEEDR;
    uint32_t pull_reg = gpio_port->PUPDR;
    uint32_t bssr_reg = gpio_port->BSRR;

    //port init loop//
    for(uint8_t pin = 0; pin < 16; pin++){
        //Pin mask check to speed up loop//
        if((config->pin_mask & (1 << pin)) == 0U) {continue;}
        //otherwise  init pin//
        set_pin_mode(mode_reg, pin, config->mode);
        set_pin_output_type(otype_reg, pin, config->output_type);
        set_pin_speed(speed_reg, pin, config->speed);
        set_pin_pull(pull_reg, pin, config->pull);
        set_pin_alternate_function(gpio_port, pin, config->alternate_function);
        set_pin_state(bssr_reg, pin, config->pin_state);
    }

    //write updated values back to GPIO port//
    gpio_port->MODER = mode_reg;
    gpio_port->OTYPER = otype_reg;
    gpio_port->OSPEEDR = speed_reg;
    gpio_port->PUPDR = pull_reg;
    gpio_port->BSRR = bssr_reg;

    return(GPIO_SUCCESS);
}

