#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[4]; // Store ADC values for 4 channels

void AD_Init(void);
void AD_GetValue(void);

#endif
