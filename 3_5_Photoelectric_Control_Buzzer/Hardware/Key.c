#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // Enable clock for GPIOB
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11; // Configure PB0 and PB1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          // Input with pull-up
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // Speed setting (not critical for input)
    GPIO_Init(GPIOB, &GPIO_InitStructure);                 // Initialize GPIOB with the configuration
}

uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;

    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
    {
        Delay_ms(20); // Debounce delay
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0); // Wait for key release
        Delay_ms(20); // Debounce delay
        KeyNum = 1; // Key 1 pressed
    }

    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
    {
        Delay_ms(20); // Debounce delay
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0); // Wait for key release
        Delay_ms(20); // Debounce delay
        KeyNum = 2; // Key 2 pressed
    }

    return KeyNum;
}
