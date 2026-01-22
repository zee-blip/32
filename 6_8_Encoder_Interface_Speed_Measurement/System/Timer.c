#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable clock for TIM2

    TIM_InternalClockConfig(TIM2); // Configure TIM2 to use internal clock

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1; // Set prescaler to have 10 kHz timer clock (assuming 72 MHz system clock)
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Upcounting mode
    TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1; // Set period for 10000 counts (1 second overflow)
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; // No repetition
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update); // Clear update flag
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Enable update interrupt

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // Set priority grouping

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn; // TIM2 interrupt channel
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; // Pre
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; // Subpriority
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; // Enable the IRQ channel
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2, ENABLE); // Start TIM2
}

// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // Check if update interrupt flag is set
//     {
//          // User code to be executed on timer overflow
//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // Clear the interrupt flag
//     }
// }
