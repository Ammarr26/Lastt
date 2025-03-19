#include <stdint.h>
 #include <stm32f401xx.h>
 
 #define BUTTON1_PIN 1
 #define BUTTON2_PIN 2
 #define BUTTON3_PIN 3
 #define BUTTON4_PIN 4
 
 #define GREENLED_PIN 5
 #define REDLED_PIN 6
 #define BUZZER_PIN 7
 
 int main(void)
 {
     int sequence[] = {1, 2, 3, 4};
     int input[4];
     int index = 0;
     RCC->AHB1ENR |= (1 << 0);
 
     GPIOA->MODER |= ((1 << 2*GREENLED_PIN) | (1 << 2*REDLED_PIN) | (1 << 2*BUZZER_PIN));
     GPIOA->MODER &= ~((0b11 << 2 * BUTTON1_PIN) | (0b11 << 2 * BUTTON2_PIN) | (0b11 << 2 * BUTTON3_PIN) | (0b11 << 2 * BUTTON4_PIN));
     GPIOA->PUPDR |= ((0b10 << 2 * BUTTON1_PIN) | (0b10 << 2 * BUTTON2_PIN) | (0b10 << 2 * BUTTON3_PIN) | (0b10 << 2 * BUTTON4_PIN));
 
     while(1)
     {
         if(GPIOA->IDR & (1 << BUTTON1_PIN) && index < 4)
         {
             input[index++] = 1;
             while(GPIOA->IDR & (1 << BUTTON1_PIN) && index < 4);
         }


         if(GPIOA->IDR & (1 << BUTTON2_PIN) && index < 4)
         {
             input[index++] = 2;
             while(GPIOA->IDR & (1 << BUTTON2_PIN) && index < 4);
         }


         if(GPIOA->IDR & (1 << BUTTON3_PIN) && index < 4)
         {
             input[index++] = 3;
             while(GPIOA->IDR & (1 << BUTTON3_PIN) && index < 4);
         }


         if(GPIOA->IDR & (1 << BUTTON4_PIN) && index < 4)
         {
             input[index++] = 4;
             while(GPIOA->IDR & (1 << BUTTON4_PIN) && index < 4);
         }


         if(index == 4)
         {
             int match = 1;
             for(int i = 0; i < 4; i++)
             {
                 if(input[i] != sequence[i])
                 {
                     match=0;
                     break;
                 }
             }
 
             if(match)
             {
                 GPIOA->ODR = (1 << GREENLED_PIN);
             }
             
             else
             {
                 GPIOA->ODR = ((1 << REDLED_PIN) | (1 << BUZZER_PIN));
             }
             index = 0;
         }
     }
 }


 //---------------------------------------------------------------------------------------------------------------


#include <stdint.h>
#include <stm32f401xx.h>

#define LM35_PIN 0
#define GREENLED_PIN 1
#define YELLOWLED_PIN 2
#define REDLED_PIN 3
#define BUZZER_PIN 7
#define FAN_PIN 8
#define BUTTON_PIN 10

int main(void)
{
//Enable Clocks
RCC->AHB1ENR |= (0b01 << 0); // GPIOA
RCC->APB2ENR |= (0b01 << 8); // ADC1

ADC1->CR2 |= (0b01 << 0);   // Enable ADC
for(int i = 0; i < 1000; ++i);
ADC1->CR1 |= (0b00 << 24);  // 12 bit

ADC1->SQR3 = 0;      	   // Channel 0 -> PA0

//OUTPUTs
GPIOA->MODER |= ((1 << (2 * GREENLED_PIN) )| (1 << (2 * YELLOWLED_PIN)) | (1 << (2 * REDLED_PIN) )| (1 << (2 * FAN_PIN)) |( 1 << (2 * BUZZER_PIN)));

//INPUTs
GPIOA->MODER &= ~(0b11 << (2 * BUTTON_PIN));
GPIOA->PUPDR |= (0b10 << (2 * BUTTON_PIN));

GPIOA->MODER |= (0b11 << (2 * LM35_PIN)); // Set PA0 as analog input


while(1){
	// Start conversion
	ADC1->CR2 |= (1 << 30);

	while(!(ADC1->SR & (1 << 1))); // Check End Of Conversion

	int ADC_read = ADC1->DR;
	int temp = ((ADC_read * 3.3)/ 4095)*100;

	
	if(temp <= 25)
	{
		GPIOA->ODR = (1 << GREENLED_PIN);
	}
	if(temp < 35 && temp > 25)
	{
		GPIOA->ODR = ((1 << YELLOWLED_PIN) | (1 << FAN_PIN));
	}
	if(temp > 35 && temp < 45)
	{
		GPIOA->ODR = ((1 << REDLED_PIN) | (1 << FAN_PIN));
	}
	if(temp > 45)
	{
		GPIOA->ODR = ((1 << REDLED_PIN) | (1 << BUZZER_PIN));

	}
	if(GPIOA->IDR &( 1 <<BUTTON_PIN ))
	{
	    GPIOA->ODR &=~((1<<REDLED_PIN) | (1 << FAN_PIN) | (1<<GREENLED_PIN) | (1<<YELLOWLED_PIN) | (1<<BUZZER_PIN)); 
	}
}
}