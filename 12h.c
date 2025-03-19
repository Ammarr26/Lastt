#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdint.h>  // For standard integer types

#define GPIOA_BASEADDRESS 0x40020000   // Base address for GPIOA
#define GPIOB_BASEADDRESS 0x40020400
#define GPIOC_BASEADDRESS 0x40020800

typedef struct
{
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
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASEADDRESS)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASEADDRESS)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASEADDRESS)



#define RCC_BASEADDRESS 0x40023800U  // Base address for RCC

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef*) RCC_BASEADDRESS)

#define LED1_PIN 0   // Pin for LED1 (PA0)
#define LED2_PIN 1   // Pin for LED2 (PA1)
#define LED3_PIN 2   // Pin for LED3 (PA2)
#define BUTTON_PIN 3 // Pin for Button (PA3)

void GPIO_Init(void);
void Lamp_Control(uint8_t lampNumber);
void delay_ms(int delay);
uint8_t Button_Read(void);

#endif /* STM32F401XX_H_ */