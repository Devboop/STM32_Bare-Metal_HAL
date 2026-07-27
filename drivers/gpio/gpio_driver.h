#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>

// RCC base address for clock control //
#define RCC (*(volatile uint32_t *)0x40023800UL)

// GPIO base addresses for STM32F4 series microcontrollers //
#define GPIOA ((GPIO_t *)0x40020000UL)
#define GPIOB ((GPIO_t *)0x40020400UL)
#define GPIOC ((GPIO_t *)0x40020800UL)
#define GPIOD ((GPIO_t *)0x40020C00UL)
#define GPIOE ((GPIO_t *)0x40021000UL)
#define GPIOF ((GPIO_t *)0x40021400UL)
#define GPIOG ((GPIO_t *)0x40021800UL)
#define GPIOH ((GPIO_t *)0x40021C00UL)


// Bit manipulation macros //
#define SET_BIT(gpio_reg, bit) ((gpio_reg) |= (1UL << (bit)))
#define CLEAR_BIT(gpio_reg, bit) ((gpio_reg) &= ~(1UL << (bit)))
#define READ_BIT(gpio_reg, bit) (((gpio_reg) >> (bit)) & 0x01)
#define TOGGLE_BIT(gpio_reg, bit) ((gpio_reg) ^= (1 << (bit)))

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

// GPIO Status enumeration definition //
typedef enum{
    GPIO_SUCCESS = 0,
    GPIO_ERROR_INVALID_PIN = 1,
    GPIO_ERROR_INVALID_MODE = 2,
    GPIO_ERROR_INVALID_OUTPUT_TYPE = 3
} GPIO_status_t;

// GPIO pin mode enumeration definition //
typedef enum{
    INPUT = 0x00,
    OUTPUT = 0x01,
    ALTERNATE = 0x02,
    ANALOG = 0x03
} GPIO_pin_mode_t;

// GPIO pin output type enumeration definition //
typedef enum{
    PUSH_PULL = 0x00,
    OPEN_DRAIN = 0x01
} GPIO_pin_output_type_t;

// GPIO pin speed enumeration definition //
typedef enum{
    LOW = 0x00,
    MEDIUM = 0x01,
    HIGH = 0x02,
    VERY_HIGH = 0x03
} GPIO_pin_speed_t;

// GPIO pin pull-up/pull-down enumeration definition //
typedef enum{
    NO_PULL = 0x00,
    PULL_UP = 0x01,
    PULL_DOWN = 0x02
} GPIO_pin_pull_t;

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
} GPIO_pin_alternate_function_t;

// GPIO pin set/reset enumeration definition //
typedef enum{
    RESET,
    SET
} GPIO_pin_set_reset_t;

// Clock enum//
typedef enum {
    OFF = 0x0,
    ON = 0x1
} clock_status_t;

// GPIO Config Structure definition //
typedef struct{
    uint16_t pin_mask; // Pin mask for the GPIO pins to be configured
    GPIO_pin_mode_t mode; // Mode for the GPIO pins (input, output, alternate function, analog)
    GPIO_pin_output_type_t output_type; // Output type for the GPIO pins (push-pull, open-drain)
    GPIO_pin_speed_t speed; // Speed for the GPIO pins (low, medium, high, very high)
    GPIO_pin_pull_t pull; // Pull-up/pull-down configuration for the GPIO pins (no pull, pull-up, pull-down)   
    GPIO_pin_alternate_function_t alternate_function; // Alternate function for the GPIO pins (AF0 to AF15)
    GPIO_pin_set_reset_t pin_state; // Set/reset configuration for the GPIO pins (set, reset)
} GPIO_config_t;

// Set GPIO pin mode function definition //
void set_pin_mode(uint32_t gpio_reg, uint8_t pin, GPIO_pin_mode_t mode);

// Set GPIO pin output type function definition //
void set_pin_output_type(uint32_t gpio_reg, uint8_t pin, GPIO_pin_output_type_t output_type);

// Set GPIO pin speed function definition //
void set_pin_speed(uint32_t gpio_reg, uint8_t pin, GPIO_pin_speed_t speed);

// Set GPIO pin pull-up/pull-down function definition //
void set_pin_pull(uint32_t gpio_reg, uint8_t pin, GPIO_pin_pull_t pull);

// Set GPIO pin alternate function function definition //
void set_pin_alternate_function(GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function_t af);

// Bit set/reset function definition //
void set_pin_state(uint32_t gpio_reg, uint8_t pin, GPIO_pin_set_reset_t set_reset);

void clock_init();

//GPIO initialization function definition //
GPIO_status_t gpio_init(GPIO_t *gpio_port, const GPIO_config_t *config);

#endif // GPIO_DRIVER_H