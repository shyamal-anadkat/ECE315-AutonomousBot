#include "interrupts.h"
#include "boardUtil.h"

/*
Create a UART ISR in interrupts.c that alerts the main program when a valid distance has arrived (Refer to range
finder’s datasheet for more information parsing to obtain valid distance)
Circular Buffers need not be implemented but UART FIFOs should be enabled.
*/
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

//*****PORTING OVER FROM LAB3**************//

// GPIOF HANDLER (PF0 and PF1)
void GPIOF_Handler(void){
		if(GPIOF->RIS & PF0){
			//leftA_pulse++;
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

