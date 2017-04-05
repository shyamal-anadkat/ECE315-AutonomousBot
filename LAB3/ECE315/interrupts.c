#include "interrupts.h"

volatile static uint32_t left_pulse = 0;
volatile static uint32_t right_pulse = 0;

void GPIOF_Handler(void){
	left_pulse++;
	GPIOF->ICR |= 1;
}


void GPIOC_Handler(void){
	right_pulse++;
	GPIOC->ICR |= 1;
}
