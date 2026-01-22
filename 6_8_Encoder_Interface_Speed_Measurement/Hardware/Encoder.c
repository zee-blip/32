#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
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
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // PA6: TIM3_CH1, PA7: TIM3_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //Input Pull-Up
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Time base configuration
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1; // Prescaler
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Upcounting mode
    TIM_TimeBaseInitStruct.TIM_Period = 65536 - 1; // ARR/[Set period for 10000 counts (1 second overflow)]
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; // No repetition
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    // PWM Input configuration (输入捕获单元配置)
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure); // Initialize structure with default values
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; // Channel 1
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // Rising edge(在编码器功能应用中代表高低电平极性不反转，不代表上升沿有效，因为编码器接口是双边沿捕获)
    TIM_ICInitStructure.TIM_ICFilter = 0xF; // No filter
    TIM_ICInit(TIM3, &TIM_ICInitStructure); 
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; // Channel 2
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // Rising edge(在编码器功能应用中代表高低电平极性不反转，不代表上升沿有效，因为编码器接口是双边沿捕获)
    TIM_ICInitStructure.TIM_ICFilter = 0xF; // No filter
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // Configure TIM3 as Encoder Interface
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE); // Enable TIM3
}

int16_t Encoder_Get(void)
{
    int16_t Temp;
    Temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0); // Clear the counter after reading
    return Temp; // Return the current count value of TIM3
}
