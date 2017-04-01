#include "interrupts.h"

extern volatile bool alert1s;

void SysTick_Handler(void){
	
	uint32_t val;
	alert1s = true;
	val = SysTick->VAL;
}
