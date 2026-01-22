#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	int i;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;
	// GPIO_InitStructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1)
	{
		for(i=0; i<8; i++)
		{
			GPIO_Write(GPIOA, ~(0000000000000001<<i));	//0000 0000 0000 0001
			Delay_ms(500);
		}
	}
}

