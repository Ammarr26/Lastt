#ifndef STM32F401XX_H_
#define STM32F401XX_H_

#include <stdint.h>

#define GPIOA_BASEADDRESS 0x40020000   // Base address for GPIOA

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


//=================================================================================================


 #ifndef INC_STM32F401XX_H_
 #define INC_STM32F401XX_H_
 
 #define GPIOA_BASEADDR 0x40020000
 
 #define RCC_BASEADDR 0x40023800
 
 #define ADC_BASEADDR 0x40012000

 typedef struct {
     volatile int MODER;    /**< GPIO port mode register (offset 0x00) */
     volatile int OTYPER;   /**< GPIO port output type register (offset 0x04) */
     volatile int OSPEEDR;  /**< GPIO port output speed register (offset 0x08) */
     volatile int PUPDR;    /**< GPIO port pull-up/pull-down register (offset 0x0C) */
     volatile int IDR;      /**< GPIO port input data register (offset 0x10) */
     volatile int ODR;      /**< GPIO port output data register (offset 0x14) */
     volatile int BSRR;     /**< GPIO port bit set/reset register (offset 0x18) */
     volatile int LCKR;     /**< GPIO port configuration lock register (offset 0x1C) */
     volatile int AFR[2];   /**< GPIO alternate function registers (offset 0x20-0x24) */
 } GPIO_RegDef_t;
 

 #define GPIOA ((GPIO_RegDef_t*) GPIOA_BASEADDR)
 
 typedef struct {
     volatile int CR;         /**< Clock control register (offset 0x00) */
     volatile int PLLCFGR;    /**< PLL configuration register (offset 0x04) */
     volatile int CFGR;       /**< Clock configuration register (offset 0x08) */
     volatile int CIR;        /**< Clock interrupt register (offset 0x0C) */
     volatile int AHB1RSTR;   /**< AHB1 peripheral reset register (offset 0x10) */
     volatile int AHB2RSTR;   /**< AHB2 peripheral reset register (offset 0x14) */
     volatile int RESERVED0[2]; /**< Reserved (offset 0x18-0x1C) */
     volatile int APB1RSTR;   /**< APB1 peripheral reset register (offset 0x20) */
     volatile int APB2RSTR;   /**< APB2 peripheral reset register (offset 0x24) */
     volatile int RESERVED1[2]; /**< Reserved (offset 0x28-0x2C) */
     volatile int AHB1ENR;    /**< AHB1 peripheral clock enable register (offset 0x30) */
     volatile int AHB2ENR;    /**< AHB2 peripheral clock enable register (offset 0x34) */
     volatile int RESERVED2[2]; /**< Reserved (offset 0x38-0x3C) */
     volatile int APB1ENR;    /**< APB1 peripheral clock enable register (offset 0x40) */
     volatile int APB2ENR;    /**< APB2 peripheral clock enable register (offset 0x44) */
 } RCC_RegDef_t;
 

 #define RCC ((RCC_RegDef_t*) RCC_BASEADDR)
 
 typedef struct{
     volatile int SR;
     volatile int CR1;
     volatile int CR2;
     volatile int SMPR1;
     volatile int SMPR2;
     volatile int JOFR1;
     volatile int JOFR2;
     volatile int JOFR3;
     volatile int JOFR4;
     volatile int HTR;
     volatile int LTR;
     volatile int SQR1;
     volatile int SQR2;
     volatile int SQR3;
     volatile int JSQR;
     volatile int JDR1;
     volatile int JDR2;
     volatile int JDR3;
     volatile int JDR4;
     volatile int DR;
     volatile int CCR;
 }ADC_RegDef_t;
 
 #define ADC1 ((ADC_RegDef_t*) ADC_BASEADDR)
 
 #endif /* INC_STM32F401XX_H_ */