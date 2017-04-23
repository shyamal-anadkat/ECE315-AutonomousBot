#include "interrupts.h"
#include "boardUtil.h"

/*
Create a UART ISR in interrupts.c that alerts the main program when a valid distance has arrived (Refer to range
finder’s datasheet for more information parsing to obtain valid distance)
Circular Buffers need not be implemented but UART FIFOs should be enabled.
*/
extern volatile char leftBuf[4];
extern volatile bool AlertSysTick; //50us
extern volatile bool Alert10msA; // 10ms
extern volatile bool Alert10msB; // 10ms
extern volatile bool Alert30ms; // 30ms
extern volatile bool Alert1sA;   //  1s for display
extern volatile bool Alert1sB;   
volatile uint32_t leftA_pulse = 0;

// systick handler which keeps track of the count
void SysTick_Handler(void){
	
	uint32_t val;
	static uint32_t cnt1 = 0;
	static uint32_t cnt2 = 0;
	static uint32_t cnt3 = 0;
	static uint32_t cnt4 = 0;
	
	AlertSysTick = true;
	
	if(!Alert10msA) {
	cnt1++;
	}
	if(!Alert1sA) {
	cnt2++;
	}
	if(!Alert30ms) {
	cnt3++;
	}
	if(!Alert1sB) {
	cnt4++; 
	}
	
	// get the range and update count 
	if(cnt1 > 199){
		Alert10msA = true;
		//Alert10msB = true;
		cnt1 = 0;
	}
	
	if(cnt3 > 599) {
		Alert30ms = true;
		cnt3 = 0;
	}
	
	if(cnt2 >= 20000){
		Alert1sA = true;
		Alert1sB = true;
		cnt2 = 0;
		cnt4 = 0; 
	}
	
	val = SysTick->VAL;
}



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

//*****PORTING OVER FROM LAB3**************//

// GPIOF HANDLER (PF0 and PF1)
void GPIOF_Handler(void){
		if(GPIOF->RIS & PF0){
			leftA_pulse++;
			GPIOF->ICR |= PF0;  //clear interrupt 
		}
		if(GPIOF->RIS& PF1){
			//leftB_pulse++;
			GPIOF->ICR |= PF1;	//clear interrupt 
		}
}

// GPIOC HANDLER (PC5 and PC6)
void GPIOC_Handler(void){
	if(GPIOC->RIS & PC5){
		//rightA_pulse++;
		GPIOC->ICR |= PC5;	//clear interrupt 
	}
	if(GPIOC->RIS & PC6){
		//rightB_pulse++;
		GPIOC->ICR |= PC6;	//clear interrupt 
	}
}

