#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
#include <stdint.h>

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

#define GPIOA volatile (GPIO_t *)0x40020000
#define GPIOB volatile (GPIO_t *)0x40020400
#define GPIOC volatile (GPIO_t *)0x40020800
#define GPIOD volatile (GPIO_t *)0x40020C00
#define GPIOE volatile (GPIO_t *)0x40021000
#define GPIOF volatile (GPIO_t *)0x40021400
#define GPIOG volatile (GPIO_t *)0x40021800
#define GPIOH volatile (GPIO_t *)0x40021C00

#define SET_BIT(gpio_reg, bit) (gpio_reg |= (1 << bit))
#define CLEAR_BIT(gpio_reg, bit) (gpio_reg &= ~(1 << bit))
#define READ_BIT(gpio_reg, bit) ((gpio_reg >> bit) & 0x01)
#define TOGGLE_BIT(gpio_reg, bit) (gpio_reg ^= (1 << bit))

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

void set_pin_mode(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_mode mode);
void set_pin_output_type(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_output_type output_type);
void set_pin_speed(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_speed speed);
void set_pin_pull(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_pull pull);
void set_pin_alternate_function(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_alternate_function af);
void bit_set_reset(volatile GPIO_t *gpio_port, uint8_t pin, GPIO_pin_set_reset set_reset);
void toggle_pin_with_delay(GPIO_t *gpio_port, uint8_t pin, uint32_t delay);

#endif // GPIO_DRIVER_H