#include "pwm.h"
#include "../include/sysctrl.h"

//*****************************************************************************
//*****************************************************************************
PWM0_Type *PWM;

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
	 // enabling clock gating for RCGC PWM and polling for getting ready 
		if (base ==PWM0_BASE) {
				SYSCTL->RCGCPWM |= SYSCTL_RCGCPWM_R0;
				while( (SYSCTL->PRPWM & SYSCTL_PRPWM_R0) == 0){}
			
		} else {
			  SYSCTL->RCGCPWM |=  SYSCTL_RCGCPWM_R1;
			  while( (SYSCTL->PRPWM & SYSCTL_PRPWM_R1) == 0){}
		}
		
	// sysctl -> rcc config; refer to the datasheet 
	SYSCTL->RCC &= ~0xE0000;
	SYSCTL->RCC |= 0x100000;
		
	//if(!verify_uart_base(base)) return 0;
	PWM = (PWM0_Type*) base;
	
		/*PB5 will need to be programmed similarly. cmpa and gena are used to set the behavior of PB4. cmpb and genb are used to
      set the behavior of PB5. The important thing to recognize that both signals for a PWM generator shares the LOAD register but
      that GENA is independent of GENB and CMPA is independent of CMPB */
		
	if(pwm_generator == 0){
		PWM->_0_CTL &= ~1;
		PWM->_0_LOAD = load;
		PWM->_0_CMPA = cmpa;
		PWM->_0_CMPB = cmpb;
		PWM->_0_GENA = gena;
		PWM->_0_GENB = genb;
		PWM->_0_CTL |= 1;
		PWM->ENABLE = PWM_ENABLE_PWM0A | PWM_ENABLE_PWM0B;	//enable the PWM signals.
	} else if(pwm_generator == 1){
		PWM->_1_CTL &= ~1;
		PWM->_1_LOAD = load;
		PWM->_1_CMPA = cmpa;
		PWM->_1_CMPB = cmpb;
		PWM->_1_GENA = gena;
		PWM->_1_GENB = genb;
		PWM->_1_CTL |= 1;
		PWM->ENABLE = PWM_ENABLE_PWM1A | PWM_ENABLE_PWM1B;
	} else if(pwm_generator == 2){
		PWM->_2_CTL &= ~1;
		PWM->_2_LOAD = load;
		PWM->_2_CMPA = cmpa;
		PWM->_2_CMPB = cmpb;
		PWM->_2_GENA = gena;
		PWM->_2_GENB = genb;
		PWM->_2_CTL |= 1;
		PWM->ENABLE = PWM_ENABLE_PWM2A | PWM_ENABLE_PWM2B;
	} else if(pwm_generator == 3){
		PWM->_2_CTL &= ~1;
		PWM->_3_LOAD = load;
		PWM->_3_CMPA = cmpa;
		PWM->_3_CMPB = cmpb;
		PWM->_2_GENA = gena;
		PWM->_3_GENB = genb;
		PWM->_3_CTL |= 1;
		PWM->ENABLE = PWM_ENABLE_PWM3A | PWM_ENABLE_PWM3B;
	}

  return 0;
}