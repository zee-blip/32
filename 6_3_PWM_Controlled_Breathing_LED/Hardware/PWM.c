#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    
    // Enable clock for GPIOA (assuming PWM output on PA0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // Enable clock for Alternate Function IO
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); // Remap TIM2 CH1 PA0 to PA15
    // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // Disable JTAG to free up pins（JTAG-DP{Debug Port}:PA15..）

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2); // Configure TIM2 to use internal clock

    // Time base configuration
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1; // Prescaler/[Set prescaler to have 10 kHz timer clock (assuming 72 MHz system clock)]
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Upcounting mode
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1; // ARR/[Set period for 10000 counts (1 second overflow)]
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; // No repetition
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // PWM mode configuration on Output Channel 1
    TIM_OCInitTypeDef TIM_OCInitStructer;
    TIM_OCStructInit(&TIM_OCInitStructer); // Initialize structure with default values
    TIM_OCInitStructer.TIM_OCMode = TIM_OCMode_PWM1; // PWM mode 1
    TIM_OCInitStructer.TIM_OCPolarity = TIM_OCPolarity_High; // Active high
    TIM_OCInitStructer.TIM_OutputState = ENABLE; // Enable output
    TIM_OCInitStructer.TIM_Pulse = 0; // CCR/[Initial pulse width (0% duty cycle)]
    TIM_OC1Init(TIM2, &TIM_OCInitStructer); // Initialize PWM on Channel 1

    TIM_Cmd(TIM2, ENABLE); // Start TIM2
}

void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}
