#include "pwm.h"



//*****************************************************************************
//*****************************************************************************
uint8_t pwmConfig(
  uint32_t base,
  uint8_t pwm_generator, 
  uint32_t load, 
  uint32_t cmpa, 
  uint32_t cmpb,
  uint32_t gena,
  uint32_t genb
)
{
	// Follows 20.4 (pg 1240)
	SYSCTL->RCGCPWM = 0x0010.0000;
	SYSCTL->RCGC2 = 0x003F;	// GPIOA-F
	//GPIOAFSEL-> = ?? // AIN0: pin6, AIN1: pin7
	//
	// SYSCTL->RCC = USEPWMDIV ??
	if(!verify_uart_base(base)) return 0;
	PWM0_BASE PWM0 = (PWM0_BASE*) base;
	
	if(pwm_generator == 0){
		PWM0->_0_LOAD = load;
		PWM0->_0_CMPA = cmpa;
		PWM0->_0_CMPB = cmpb;
		PWM0->_0_GENA = gena;
		PWM0->_0_GENB = genb;
	} else if(pwm_generator == 1){
		PWM0->_1_LOAD = load;
		PWM0->_1_CMPA = cmpa;
		PWM0->_1_CMPB = cmpb;
		PWM0->_1_GENA = gena;
		PWM0->_1_GENB = genb;
	} else if(pwm_generator == 2){
		PWM0->_2_LOAD = load;
		PWM0->_2_CMPA = cmpa;
		PWM0->_2_CMPB = cmpb;
		PWM0->_2_GENA = gena;
		PWM0->_2_GENB = genb;
	} else if(pwm_generator == 3){
		PWM0->_3_LOAD = load;
		PWM0->_3_CMPA = cmpa;
		PWM0->_3_CMPB = cmpb;
		PWM0->_2_GENA = gena;
		PWM0->_3_GENB = genb;
	}
  return 0;
}
