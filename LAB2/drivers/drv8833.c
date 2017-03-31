#include "drv8833.h"

#define PWM_LOAD_VAL    10000
#define PWM_CHANNEL_PWM   (PWM_GEN_ACTCMPAD_LOW | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_LOW   (PWM_GEN_ACTCMPBD_LOW | PWM_GEN_ACTLOAD_LOW | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_HIGH  (PWM_GEN_ACTCMPBD_HIGH | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)

//*****************************************************************************
// Initializes the 6 pins needed to control the DRV8833
//*****************************************************************************
void  drv8833_gpioInit(void)
{
	  // Configure PB4, PB5, PE4, PE5 as the PWM peripheral in the alternate function register
	
	  gpio_enable_port(GPIOB_BASE);
		gpio_enable_port(GPIOE_BASE);
		gpio_enable_port(GPIOF_BASE);
		
		gpio_config_digital_enable(GPIOB_BASE, PB4 | PB5);
		gpio_config_digital_enable(GPIOE_BASE, PE4 | PE5);
		gpio_config_enable_output(GPIOB_BASE, PB4 | PB5);
		gpio_config_enable_output(GPIOE_BASE, PE4 | PE5);
	
		gpio_config_alternate_function(GPIOB_BASE, PB4 | PB5);
		gpio_config_alternate_function(GPIOE_BASE, PE4 | PE5);
	
		gpio_config_port_control(GPIOB_BASE, GPIO_PCTL_PB4_M0PWM2 | GPIO_PCTL_PB5_M0PWM3);
		gpio_config_port_control(GPIOE_BASE, GPIO_PCTL_PE4_M1PWM2 | GPIO_PCTL_PE5_M1PWM3);
	
	  // Configure PF2 as a digital input
    // Configure PF3 as a digital output and set it to 1

		gpio_config_digital_enable(GPIOF_BASE, PF2 | PF3);
		gpio_config_enable_input(GPIOF_BASE, PF2);
		gpio_config_enable_output(GPIOF_BASE, PF3);
	
		GPIOF->DATA |= PF3;
		SYSCTL->RCGCPWM |= SYSCTL_RCGCPWM_R0 | SYSCTL_RCGCPWM_R1;
  
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftForward(uint8_t dutyCycle)
{
  
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftReverse(uint8_t dutyCycle)
{
}


//*****************************************************************************
//*****************************************************************************
void  drv8833_rightForward(uint8_t dutyCycle)
{
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_rightReverse(uint8_t dutyCycle)
{
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnLeft(uint8_t dutyCycle)
{
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnRight(uint8_t dutyCycle)
{
}
