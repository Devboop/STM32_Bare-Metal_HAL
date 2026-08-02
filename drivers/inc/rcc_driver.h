/**
 * @file rcc_driver.h
 * @author Dominick Green
 * @brief RCC driver header file
 * @version 0.1
 * @date 2024-06-05
 */
#pragma once 

#include <stdint.h>
#include <stddef.h>

/**
 * @brief RCC base address for clock control
 */
#define RCC ((RCC_t *)0x40023800UL)

/**
 * @brief RCC register structure definition
 */
typedef struct{
    volatile uint32_t CR;
    volatile uint32_t PLL_CFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} RCC_t;

/**
 * @brief Static assertions to ensure correct offsets of RCC registers
 */
_Static_assert(offsetof(RCC_t, APB1RSTR)  == 0x20, "");
_Static_assert(offsetof(RCC_t, AHB1ENR)   == 0x30, "");
_Static_assert(offsetof(RCC_t, APB1ENR)   == 0x40, "");
_Static_assert(offsetof(RCC_t, AHB1LPENR) == 0x50, "");
_Static_assert(offsetof(RCC_t, APB1LPENR) == 0x60, "");
_Static_assert(offsetof(RCC_t, BDCR)      == 0x70, "");
_Static_assert(offsetof(RCC_t, SSCGR)     == 0x80, "");
_Static_assert(sizeof(RCC_t)              == 0x98, "");

/**
 * @brief RCC clock status enumeration
 */
typedef enum {
    RCC_CLK_OFF = 0x0,
    RCC_CLK_ON = 0x1
} rcc_status_t;

/**
 * @brief AHB1 clock port enumeration
 */
typedef enum {
    RCC_AHB1_GPIOA = 0UL,
    RCC_AHB1_GPIOB = 1UL,
    RCC_AHB1_GPIOC = 2UL,
    RCC_AHB1_GPIOD = 3UL,
    RCC_AHB1_GPIOE = 4UL,
    RCC_AHB1_GPIOF = 5UL,
    RCC_AHB1_GPIOG = 6UL,
    RCC_AHB1_GPIOH = 7UL,
    RCC_AHB1_CRC = 12UL,
    RCC_AHB1_BKPSRAM = 18UL,
    RCC_AHB1_DMA1 = 21UL,
    RCC_AHB1_DMA2 = 22UL,
    RCC_AHB1_OTGHS = 29UL,
    RCC_AHB1_OTGHSULPI = 30UL  
} ahb1_clock_port_t;


/**
 * @brief AHB1 GPIO Clock Enable Function
 * @param port AHB1 clock port
 * @param clock_status Clock status
 */
void rcc_ahb1_clock_enable(ahb1_clock_port_t port, rcc_status_t clock_status);