#include "interrupts.h"
#include "boardUtil.h"

volatile uint32_t leftA_pulse = 0;
volatile uint32_t leftB_pulse = 0;
volatile uint32_t rightA_pulse = 0;
volatile uint32_t rightB_pulse = 0;

void GPIOF_Handler(void){
		if(GPIOF->RIS & PF0){
			leftA_pulse++;
			GPIOF->ICR |= PF0;
		}
		if(GPIOF->RIS& PF1){
			leftB_pulse++;
			GPIOF->ICR |= PF1;
		}
}


void GPIOC_Handler(void){
	if(GPIOC->RIS & PC5){
		rightA_pulse++;
		GPIOC->ICR |= PC5;
	}
	if(GPIOC->RIS & PC6){
		rightB_pulse++;
		GPIOC->ICR |= PC6;
	}
}