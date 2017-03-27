#include "interrupts.h"
#include "adc.h"

volatile bool measureAnalog; 

int SysTick_Handler(void) {
	static int count = 0; 
	int anval;
	
	if(count == 199) {
		count = 0;
		measureAnalog = true;
	} 
	count = (count + 1) % 200; 
	
	return count; 
}
