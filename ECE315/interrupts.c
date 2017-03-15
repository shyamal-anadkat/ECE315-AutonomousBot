#include "interrupts.h"
#include "adc.h"

volatile bool isdone; 

int SysTick_Handler(void) {
static int count = 0; 
	int anval;
	
	if(count == 200) {
		count = 0;
		isdone = true;
	} 
	count++; 
	
	return count; 
}