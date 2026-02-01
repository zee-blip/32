#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();
	
	Serial_Init();

	// Serial_SendByte(0x41);
	
	//uint8_t MyArray[]={0x42,0x43,0x44,0x45,0x46};
	//Serial_SendArray(MyArray,sizeof(MyArray)/sizeof(MyArray[0]));
	
	// Serial_SendString("Hello, STM32!\r\n");

	// Serial_SendNumber(12345, 5);
	
	// printf("Num=%d\r\n",666);

	// char String[100];
	// sprintf(String,"Num=%d\r\n",666);
	// Serial_SendString(String);
	
	Serial_Printf("Num=%d\r\n",666);

	while (1)
	{
		
	}
}
