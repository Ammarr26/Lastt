#include <stdint.h>
#include <stdbool.h>
#include "stm32.f401xx.h"

// Buttons
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define BUTTON4 4
#define RESET_BUTTON 5

// LEDs
#define GREEN_LED 6
#define RED_LED 7

// Buzzer
#define BUZZER 8

void Enable_Clock(void);
void GPIO_Init(void);

int default_password[] = {4, 3, 1, 2};
int sequence[4];
int index = 0;
bool correct = true;

int main(void)
{
    Enable_Clock();
    GPIO_Init();

    /* Loop forever */
    for (;;)
    {
        // Step 1: Check for pressed buttons
        if (index < 4)
        {
            if ((GPIOA->IDR >> BUTTON1) & 1)
            {
                sequence[index] = 1;
                index++;
                while ((GPIOA->IDR >> BUTTON1) & 1);
            }
            if ((GPIOA->IDR >> BUTTON2) & 1)
            {
                sequence[index] = 2;
                index++;
                while ((GPIOA->IDR >> BUTTON2) & 1);
            }
            if ((GPIOA->IDR >> BUTTON3) & 1)
            {
                sequence[index] = 3;
                index++;
                while ((GPIOA->IDR >> BUTTON3) & 1);
            }
            if ((GPIOA->IDR >> BUTTON4) & 1)
            {
                sequence[index] = 4;
                index++;
                while ((GPIOA->IDR >> BUTTON4) & 1);
            }
        }

        // Step 2: Check sequence
        if (index == 4)
        {
            correct = true; // Reset correct status for each attempt
            for (int i = 0; i < 4; i++)
            {
                if (sequence[i] != default_password[i])
                {
                    correct = false;
                    break;
                }
            }
            if (correct)
            {
                GPIOA->ODR |= (1 << GREEN_LED);
                GPIOA->ODR &= ~(1 << RED_LED);
                GPIOA->ODR &= ~(1 << BUZZER);
            }
            else
            {
                GPIOA->ODR &= ~(1 << GREEN_LED);
                for (int i = 0; i < 4; i++)
                {
                    GPIOA->ODR ^= (1 << RED_LED);
                    GPIOA->ODR ^= (1 << BUZZER);
                    for (volatile int delay = 0; delay < 100000; delay++); // Adjust delay for visibility
                }
            }
            index = 0; // Reset index after checking
        }

        // Step 3: Reset System
        if ((GPIOA->IDR >> RESET_BUTTON) & 1)
        {
            index = 0;
            GPIOA->ODR &= ~(1 << RED_LED);
            GPIOA->ODR &= ~(1 << BUZZER);
            GPIOA->ODR &= ~(1 << GREEN_LED);
            while ((GPIOA->IDR >> RESET_BUTTON) & 1);
        }
    }
}

void Enable_Clock(void)
{
    RCC->AHB1ENR |= (1 << 0) | (1 << 1);
}

void GPIO_Init(void)
{
    // Default: input for all buttons
    GPIOA->MODER &= ~(0b11 << (BUTTON1 * 2)) | ~(0b11 << (BUTTON2 * 2)) | ~(0b11 << (BUTTON3 * 2)) | ~(0b11 << (BUTTON4 * 2)) | ~(0b11 << (RESET_BUTTON * 2));

    // LED and buzzer
    GPIOA->MODER |= (0b01 << (GREEN_LED * 2)) | (0b01 << (RED_LED * 2)) | (0b01 << (BUZZER * 2));

    // Pull-down resistors for buttons
    GPIOA->PUPDR |= (0b10 << (BUTTON1 * 2)) | (0b10 << (BUTTON2 * 2)) | (0b10 << (BUTTON3 * 2)) | (0b10 << (BUTTON4 * 2)) | (0b10 << (RESET_BUTTON * 2));
}