/**
 * @file gpio_driver.h 
 * @author Dominick Green (greendom99@gmail.com)
 * @brief GPIO Driver for STM32F4xx series microcontrollers
 * @version 0.1
 * @date 2026-07-26
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

/**
 * @brief GPIO port base addresses
 */
#define GPIOA ((GPIO_t *)0x40020000UL)
#define GPIOB ((GPIO_t *)0x40020400UL)
#define GPIOC ((GPIO_t *)0x40020800UL)
#define GPIOD ((GPIO_t *)0x40020C00UL)
#define GPIOE ((GPIO_t *)0x40021000UL)
#define GPIOF ((GPIO_t *)0x40021400UL)
#define GPIOG ((GPIO_t *)0x40021800UL)
#define GPIOH ((GPIO_t *)0x40021C00UL)


/**
 * @brief Bit manipulation macros
 */
#define SET_BIT(gpio_reg, bit) ((gpio_reg) |= (1UL << (bit)))
#define CLEAR_BIT(gpio_reg, bit) ((gpio_reg) &= ~(1UL << (bit)))
#define READ_BIT(gpio_reg, bit) (((gpio_reg) >> (bit)) & 0x01)
#define TOGGLE_BIT(gpio_reg, bit) ((gpio_reg) ^= (1 << (bit)))

/**
 * @brief GPIO register structure definition
 */
typedef struct{
volatile uint32_t MODER; /**< Mode register */
volatile uint32_t OTYPER; /**< Output type register */
volatile uint32_t OSPEEDR; /**< Output speed register */
volatile uint32_t PUPDR; /**< Pull-up/pull-down register */
volatile uint32_t IDR; /**< Input data register */
volatile uint32_t ODR; /**< Output data register */
volatile uint32_t BSRR; /**< Bit set/reset register */
volatile uint32_t LCKR; /**< Lock register */
volatile uint32_t AFRL; /**< Alternate function low register */
volatile uint32_t AFRH; /**< Alternate function high register */
} GPIO_t;

/**
 * @brief GPIO status enumeration
 */
typedef enum{
    GPIO_SUCCESS = 0,
    GPIO_ERROR_INVALID_PIN = 1,
    GPIO_ERROR_INVALID_MODE = 2,
    GPIO_ERROR_INVALID_OUTPUT_TYPE = 3
} GPIO_status_t;

/**
 * @brief GPIO pin mode enumeration
 */
typedef enum{
    INPUT = 0x00,
    OUTPUT = 0x01,
    ALTERNATE = 0x02,
    ANALOG = 0x03
} GPIO_pin_mode_t;

/**
 * @brief GPIO pin output type enumeration
 */
typedef enum{
    PUSH_PULL = 0x00,
    OPEN_DRAIN = 0x01
} GPIO_pin_output_type_t;

/**
 * @brief GPIO pin speed enumeration
 */
typedef enum{
    LOW = 0x00,
    MEDIUM = 0x01,
    HIGH = 0x02,
    VERY_HIGH = 0x03
} GPIO_pin_speed_t;

/**
 * @brief GPIO pin pull-up/pull-down enumeration
 */
typedef enum{
    NO_PULL = 0x00,
    PULL_UP = 0x01,
    PULL_DOWN = 0x02
} GPIO_pin_pull_t;

/**
 * @brief GPIO pin alternate function enumeration
 */
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
} GPIO_pin_alternate_function_t;

/**
 * @brief GPIO pin set/reset enumeration
 */
typedef enum{
    RESET,
    SET
} GPIO_pin_set_reset_t;

/**
 * @brief GPIO configuration structure definition
 */
typedef struct{
    uint16_t pin_mask; /**< Pin mask for the GPIO pins to be configured */
    GPIO_pin_mode_t mode; /**< Mode for the GPIO pins (input, output, alternate function, analog) */
    GPIO_pin_output_type_t output_type; /**< Output type for the GPIO pins (push-pull, open-drain) */
    GPIO_pin_speed_t speed; /**< Speed for the GPIO pins (low, medium, high, very high) */
    GPIO_pin_pull_t pull; /**< Pull-up/pull-down configuration for the GPIO pins (no pull, pull-up, pull-down) */   
    GPIO_pin_alternate_function_t alternate_function; /**< Alternate function for the GPIO pins (AF0 to AF15) */
    GPIO_pin_set_reset_t pin_state; /**< Set/reset configuration for the GPIO pins (set, reset) */
} GPIO_config_t;

/**
 * @brief GPIO pin mode function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param mode The mode to set for the specified pin (input, output, alternate function, analog)
 * @return void
 */
void set_pin_mode(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_mode_t mode);

/**
 * @brief GPIO pin output type function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param output_type The output type to set for the specified pin (push-pull, open-drain)
 * @return void
 */
void set_pin_output_type(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_output_type_t output_type);

/**
 * @brief GPIO pin speed function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param speed The speed to set for the specified pin (low, medium, high, very high)
 * @return void
 */
void set_pin_speed(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_speed_t speed);

/**
 * @brief GPIO pin pull-up/pull-down function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param pull The pull-up/pull-down configuration to set for the specified pin (no pull, pull-up, pull-down)
 * @return void
 */
void set_pin_pull(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_pull_t pull);

/**
 * @brief GPIO pin alternate function function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param af The alternate function to set for the specified pin (AF0 to AF15)
 * @return void
 */
void set_pin_alternate_function(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function_t af);

/**
 * @brief Bit set/reset function definition
 * @param gpio_port The GPIO port to modify
 * @param pin The pin number (0-15) to configure
 * @param set_reset The set/reset configuration to apply for the specified pin (set, reset)
 * @return void
 */
void set_pin_state(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_set_reset_t set_reset);

/**
 * @brief GPIO initialization function definition
 * @param gpio_port The GPIO port to initialize
 * @param config The configuration structure containing the settings for the GPIO pins
 * @return GPIO_status_t The status of the GPIO initialization (success or error code)
 */
GPIO_status_t gpio_init(GPIO_t *gpio_port, const GPIO_config_t *config);

#endif // GPIO_DRIVER_H