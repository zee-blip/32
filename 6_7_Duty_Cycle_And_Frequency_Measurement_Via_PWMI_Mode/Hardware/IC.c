#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
    // Enable clock for GPIOA (assuming PWM output on PA0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // Enable clock for Alternate Function IO
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); // Remap TIM2 CH1 PA0 to PA15
    // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // Disable JTAG to free up pins（JTAG-DP{Debug Port}:PA15..）

    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //Input Pull-Up
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM3); // Configure TIM3 to use internal clock

    // Time base configuration
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // Prescaler/[Set prescaler to have 1 MHz(Standard Frequency) timer clock (assuming 72 MHz system clock)]
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Upcounting mode
    TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1; // ARR/[Set period for 10000 counts (1 second overflow)]
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; // No repetition
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; // Channel 1
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // Rising edge
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // Direct input
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; // No prescaler
    TIM_ICInitStructure.TIM_ICFilter = 0xF; // No filter
    TIM_PWMIConfig(TIM3, &TIM_ICInitStructure); // Configure PWM Input mode

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1); // Select TI1 as input trigger
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); // Slave mode selection: Reset Mode

    TIM_Cmd(TIM3, ENABLE); // Enable TIM3
}

uint32_t IC_GetFreq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3)+1); // Frequency calculation based on 1 MHz timer clock
}

uint32_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3) + 1) * 100 / TIM_GetCapture1(TIM3); // Duty cycle(%) calculation based on 1 MHz timer clock
}
