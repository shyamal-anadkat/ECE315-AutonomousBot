#include "interrupts.h"
#include "boardUtil.h"

volatile uint32_t leftA_pulse = 0;
volatile uint32_t leftB_pulse = 0;
volatile uint32_t rightA_pulse = 0;
volatile uint32_t rightB_pulse = 0;

//***********************************************
//Handlers to count the number of pulses on both 
//encoder channels. (for all 4 GPIO pins) 
//***********************************************

// GPIOF HANDLER (PF0 and PF1)
void GPIOF_Handler(void){
		if(GPIOF->RIS & PF0){
			leftA_pulse++;
			GPIOF->ICR |= PF0;  //clear interrupt 
		}
		if(GPIOF->RIS& PF1){
			leftB_pulse++;
			GPIOF->ICR |= PF1;	//clear interrupt 
		}
}

// GPIOC HANDLER (PC5 and PC6)
void GPIOC_Handler(void){
	if(GPIOC->RIS & PC5){
		rightA_pulse++;
		GPIOC->ICR |= PC5;	//clear interrupt 
	}
	if(GPIOC->RIS & PC6){
		rightB_pulse++;
		GPIOC->ICR |= PC6;	//clear interrupt 
	}
}