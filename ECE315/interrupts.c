#include "interrupts.h"
#include "adc.h"

volatile bool measureAnalog; 
volatile bool measureDigital;

int SysTick_Handler(void) {
	static int count = 0; 
	
	measureDigital = true;
	
	if(count == 199) {
		count = 0;
		measureAnalog = true;
	} 
	count = (count + 1) % 200; 
	
	return count; 
}
