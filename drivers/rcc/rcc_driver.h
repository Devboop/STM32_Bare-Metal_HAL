#pragma once 

#include <stdint.h>

// Pointer to RCC port struct in memory //
#define RCC ((RCC_t *)0x40023800UL)


// RCC Structure //
typedef struct{
    volatile uint32_t RCC_CR;
    volatile uint32_t RCC_PLL_CFGR;
    volatile uint32_t RCC_CFGR;
    volatile uint32_t RCC_CIR;
    volatile uint32_t RCC_AHB1RSTR;
    volatile uint32_t RCC_AHB2RSTR;
    volatile uint32_t RCC_AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t RCC_APB1RSTR;
    volatile uint32_t RCC_APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t RCC_AHB1ENR;
    volatile uint32_t RCC_AHB2ENR;
    volatile uint32_t RCC_AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t RCC_APB1ENR;
    volatile uint32_t RCC_APB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t RCC_AHB1LPENR;
    volatile uint32_t RCC_AHB2LPENR;
    volatile uint32_t RCC_AHB2LPENR;
    uint32_t RESERVED4;
    volatile uint32_t RCC_APB1LPENR;
    volatile uint32_t RCC_APB2LPENR;
    uint32_t RESERVED5[2];
    volatile uint32_t RCC_BDCR;
    volatile uint32_t RCC_CSR;
    uint32_t RESERVED6[2];
    volatile uint32_t RCC_SSCGR;
    volatile uint32_t RCC_PLLI2SCFGR;
    volatile uint32_t RCC_PLLSAICFGR;
    volatile uint32_t RCC_DCKCFGR;
    volatile uint32_t RCC_CKGATENR;
    volatile uint32_t RCC_DCKCFGR2;
} RCC_t;


// Clock status enum //
typedef enum {
    OFF = 0x0,
    ON = 0x1
} rcc_status_t;

// AHB1 Clock port enum //
typedef enum {
    GPIO_PORT_A = 0UL,
    GPIO_PORT_B = 1UL,
    GPIO_PORT_C = 2UL,
    GPIO_PORT_D = 3UL,
    GPIO_PORT_E = 4UL,
    GPIO_PORT_F = 5UL,
    GPIO_PORT_G = 6UL,
    GPIO_PORT_H = 7UL,
    CRC = 12UL,
    BKPSRAM = 18UL,
    DMA1 = 21UL,
    DMA2 = 22UL,
    OTGHS = 29UL,
    OTGHSULPI = 30UL  
} ahb1_clock_port_t;


// AHB1 GPIO Clock Enable Function //
void gpio_clock_enable(ahb1_clock_port_t port, rcc_status_t clock_status);