#include <stm32f4xx.h>
#include <stdint.h>
#include <string.h>

#define BUTTON1_PIN (1 << 0)
#define BUTTON2_PIN (1 << 1)
#define BUTTON3_PIN (1 << 2)
#define BUTTON4_PIN (1 << 3)
#define RESET_PIN (1 << 4)
#define GREEN_LED_PIN (1 << 5)
#define RED_LED_PIN (1 << 6)
#define BUZZER_PIN (1 << 7)

uint8_t sequence[4] = {1, 3, 2, 4};
uint8_t input_sequence[4];
uint8_t input_index = 0;
int c = 0;

int main(void) 
{
    RCC->AHB1ENR |= (1 << 0);
    GPIOA->PUPDR |= (1 << (0 * 2)) | (1 << (1 * 2)) | (1 << (2 * 2)) | (1 << (3 * 2)) | (1 << (4 * 2));
    GPIOA->MODER |= (1 << (5 * 2)) | (1 << (6 * 2)) | (1 << (7 * 2));


    while (1) 
    {
        if (!(GPIOA->IDR & BUTTON1_PIN)) 
        {
            input_sequence[input_index++] = 1;
            while (!(GPIOA->IDR & BUTTON1_PIN));
        } 
        
        else if (!(GPIOA->IDR & BUTTON2_PIN)) 
        {
            input_sequence[input_index++] = 2;
            while (!(GPIOA->IDR & BUTTON2_PIN));
        } 
        
        else if (!(GPIOA->IDR & BUTTON3_PIN)) 
        {
            input_sequence[input_index++] = 3;
            while (!(GPIOA->IDR & BUTTON3_PIN));
        } 
        
        else if (!(GPIOA->IDR & BUTTON4_PIN)) 
        {
            input_sequence[input_index++] = 4;
            while (!(GPIOA->IDR & BUTTON4_PIN));
        }
         
        if (!(GPIOA->IDR & RESET_PIN)) 
        {
            GPIOA->ODR &= ~(RED_LED_PIN | BUZZER_PIN | GREEN_LED_PIN);
            input_index = 0;
            c = 0;
        }

        if (input_index == 4 && c == 0) 
        {
            for (int i = 0; i < 4; i++) 
            {
                if (sequence[i] == input_sequence[i]) 
                {
                    c += 1;
                }
            }

            if (c == 4) 
            {
                GPIOA->ODR = GREEN_LED_PIN;
            }
            
            else 
            {
                GPIOA->ODR = RED_LED_PIN | BUZZER_PIN;
            }
        }
    }
}




//---------------------------------------------------------------------------------------------




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
RCC->AHB1ENR |= (0b01 << 0);
RCC->APB2ENR |= (0b01 << 8);

ADC1->CR2 |= (0b01 << 0);
for(int i = 0; i < 1000; ++i);
ADC1->CR1 |= (0b00 << 24);

ADC1->SQR3 = 0;

GPIOA->MODER |= ((1 << (2 * GREENLED_PIN) )| (1 << (2 * YELLOWLED_PIN)) | (1 << (2 * REDLED_PIN) )| (1 << (2 * FAN_PIN)) |( 1 << (2 * BUZZER_PIN)));

GPIOA->MODER &= ~(0b11 << (2 * BUTTON_PIN));
GPIOA->PUPDR |= (0b10 << (2 * BUTTON_PIN));

GPIOA->MODER |= (0b11 << (2 * LM35_PIN));


while(1)
{
	ADC1->CR2 |= (1 << 30);

	while(!(ADC1->SR & (1 << 1)));

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