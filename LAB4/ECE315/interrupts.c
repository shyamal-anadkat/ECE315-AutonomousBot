#include "interrupts.h"

/*
Create a UART ISR in interrupts.c that alerts the main program when a valid distance has arrived (Refer to range
finder’s datasheet for more information parsing to obtain valid distance)
Circular Buffers need not be implemented but UART FIFOs should be enabled.
*/

extern volatile bool AlertSysTick; //50us
extern volatile bool Alert10ms; // 10ms
extern volatile bool Alert1s;   //  1s

extern volatile int toggle;
extern volatile char leftBuf[4];

// Left sensor buffer 
// UART hanedler for UART7
void UART7_Handler(void){
	// if the data is R then start collecting data
	if(UART7->DR == 'R'){
			leftBuf[0] = UART7->DR;
		  leftBuf[1] = UART7->DR;
		  leftBuf[2] = UART7->DR;
	    leftBuf[3] = NULL;
 }
}

// systick handler which keeps track of the count
void SysTick_Handler(void){
	
	uint32_t val;
	static uint32_t cnt1 = 0;
	static uint32_t cnt2 = 0;
	AlertSysTick = true;
	
	cnt1++;
	cnt2++;
	
	// get the range and update count 
	if(cnt1 > 199){
		Alert10ms = true;
		cnt1 = 0;
	}
	
	if(cnt2 >= 20000){
		Alert1s = true;
		cnt2 = 0;
	}
	
	val = SysTick->VAL;
}