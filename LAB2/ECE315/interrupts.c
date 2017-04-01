#include "interrupts.h"
extern volatile bool Alert1s;   //  1s

void SysTick_Handler(void){
		
	uint32_t val;
	static uint32_t cnt1 = 0;
	
	cnt1++;

	// get the range and update count 
	if(cnt1 >= 10){
		Alert1s = true;
		cnt1 = 0;
	}
	
	val = SysTick->VAL;
}