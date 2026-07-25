#include <stdint.h>

// GPIO register structure definition //
typedef struct{
volatile uint32_t MODER;
volatile uint32_t OTYPER;
volatile uint32_t OSPEEDR;
volatile uint32_t PUPDR;
volatile uint32_t IDR;
volatile uint32_t ODR;
volatile uint32_t BSRR;
volatile uint32_t LCKR;
volatile uint32_t AFRL;
volatile uint32_t AFRH;
} GPIO_t;

// GPIO base addresses definition //
#define GPIOA volatile (GPIO_t *)0x40020000
#define GPIOB volatile (GPIO_t *)0x40020400
#define GPIOC volatile (GPIO_t *)0x40020800
#define GPIOD volatile (GPIO_t *)0x40020C00
#define GPIOE volatile (GPIO_t *)0x40021000
#define GPIOF volatile (GPIO_t *)0x40021400
#define GPIOG volatile (GPIO_t *)0x40021800
#define GPIOH volatile (GPIO_t *)0x40021C00

//Bit manipulation macros definition //
#define SET_BIT(gpio_reg, bit) (gpio_reg |= (1 << bit))
#define CLEAR_BIT(gpio_reg, bit) (gpio_reg &= ~(1 << bit))
#define READ_BIT(gpio_reg, bit) ((gpio_reg >> bit) & 0x01)
#define TOGGLE_BIT(gpio_reg, bit) (gpio_reg ^= (1 << bit))

// GPIO pin mode enumeration definition //
typedef enum{
    INPUT = 0x00,
    OUTPUT = 0x01,
    ALTERNATE = 0x02,
    ANALOG = 0x03
} GPIO_pin_mode;

// GPIO pin output type enumeration definition //
typedef enum{
    PUSH_PULL = 0x00,
    OPEN_DRAIN = 0x01
} GPIO_pin_output_type;

// GPIO pin speed enumeration definition //
typedef enum{
    LOW = 0x00,
    MEDIUM = 0x01,
    HIGH = 0x02,
    VERY_HIGH = 0x03
} GPIO_pin_speed;

// GPIO pin pull-up/pull-down enumeration definition //
typedef enum{
    NO_PULL = 0x00,
    PULL_UP = 0x01,
    PULL_DOWN = 0x02,
    RESERVED = 0x03
} GPIO_pin_pull;

// GPIO pin alternate function enumeration definition //
typedef enum{
    AF0 = 0x00,
    AF1 = 0x01,
    AF2 = 0x02,
    AF3 = 0x03,
    AF4 = 0x04,
    AF5 = 0x05,
    AF6 = 0x06,
    AF7 = 0x07,
    AF8 = 0x08,
    AF9 = 0x09,
    AF10 = 0x0A,
    AF11 = 0x0B,
    AF12 = 0x0C,
    AF13 = 0x0D,
    AF14 = 0x0E,
    AF15 = 0x0F
} GPIO_pin_alternate_function;

// GPIO pin set/reset enumeration definition //
typedef enum{
    RESET,
    SET
} GPIO_pin_set_reset;

//Set GPIO pin mode function definition //
void set_pin_mode(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_mode mode){
    gpio_port->MODER &= ~(0x03 << (pin * 2)); // Clear the mode bits for the specified pin
    gpio_port->MODER |= (mode << (pin * 2)); // Set the new mode for the specified pin
}

void set_pin_output_type(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_output_type output_type){
    gpio_port->OTYPER &= ~(0x01 << pin); // Clear the output type bit for the specified pin
    gpio_port->OTYPER |= (output_type << pin); // Set the new output type for the specified pin
}

void set_pin_speed(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_speed speed){
    gpio_port->OSPEEDR &= ~(0x03 << (pin * 2)); // Clear the speed bits for the specified pin
    gpio_port->OSPEEDR |= (speed << (pin * 2)); // Set the new speed for the specified pin
}

void set_pin_pull(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_pull pull){
    gpio_port->PUPDR &= ~(0x03 << (pin * 2)); // Clear the pull-up/pull-down bits for the specified pin
    gpio_port->PUPDR |= (pull << (pin * 2)); // Set the new pull-up/pull-down configuration for the specified pin
}

void set_pin_alternate_function(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function af){
    if(pin < 8){
        gpio_port->AFRL &= ~(0x0F << (pin * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRL |= (af << (pin * 4)); // Set the new alternate function for the specified pin
    } else {
        gpio_port->AFRH &= ~(0x0F << ((pin - 8) * 4)); // Clear the alternate function bits for the specified pin
        gpio_port->AFRH |= (af << ((pin - 8) * 4)); // Set the new alternate function for the specified pin
    }
}

void bit_set_reset(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_set_reset set_reset){
    if(set_reset == SET){
        gpio_port->BSRR = (1 << pin); // Set the set bit for the specified pin
    } else if(set_reset == RESET){
        gpio_port->BSRR = (1 << (pin + 16)); // Set the reset bit for the specified pin
    } else {
        // Invalid set_reset value, handle error if necessary
        printf("Error: Invalid set_reset value. Use SET or RESET.\n");
    }
}

// Toggle GPIO pin with a short delay//
void toggle_pin_with_delay(GPIO_t *gpio_port, uint8_t pin, uint32_t delay){
    while(1){
        bit_set_reset(gpio_port, pin, SET); // Set the pin
        for(uint32_t i = 0; i < delay; i++); // Delay
        bit_set_reset(gpio_port, pin, RESET); // Reset the pin
        for(uint32_t i = 0; i < delay; i++); // Delay
    }
}
