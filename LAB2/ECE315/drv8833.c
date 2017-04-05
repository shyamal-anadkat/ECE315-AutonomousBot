#include "drv8833.h"


#define GPIO_PCTL_PE5_M1PWM3    0x00500000  // PWM2 PE5
#define GPIO_PCTL_PB4_M0PWM2    0x00040000  // PWM2 PB4
#define GPIO_PCTL_PB5_M0PWM3    0x00400000  // PWM3 PB5
#define GPIO_PCTL_PE4_M1PWM2    0x00050000  // PWM2 PE4


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
		
		// digital enable PB4, PB5, PE4, PE5
		gpio_config_digital_enable(GPIOB_BASE, PB4 | PB5);
		gpio_config_digital_enable(GPIOE_BASE, PE4 | PE5);
		gpio_config_enable_output(GPIOB_BASE, PB4 | PB5);
		gpio_config_enable_output(GPIOE_BASE, PE4 | PE5);
	
	  //PWM peripheral in the alternate function register
		gpio_config_alternate_function(GPIOB_BASE, PB4 | PB5);
		gpio_config_alternate_function(GPIOE_BASE, PE4 | PE5);
	
	  //configure the port control register for each GPIO pin, given mapping
		gpio_config_port_control(GPIOB_BASE, GPIO_PCTL_PB4_M0PWM2 | GPIO_PCTL_PB5_M0PWM3);
		gpio_config_port_control(GPIOE_BASE, GPIO_PCTL_PE4_M1PWM2 | GPIO_PCTL_PE5_M1PWM3);
	
	  // Configure PF2 as a digital input
    // Configure PF3 as a digital output and set it to 1
		gpio_config_digital_enable(GPIOF_BASE, PF2 | PF3);
		gpio_config_enable_input(GPIOF_BASE, PF2);
		gpio_config_enable_output(GPIOF_BASE, PF3);
	
		GPIOF->DATA |= PF3;
  
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftForward(uint8_t dutyCycle)
{
  	uint32_t val;
		val = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(PWM0_BASE,1,PWM_LOAD_VAL,val,val,PWM_CHANNEL_PWM,PWM_CHANNEL_LOW);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftReverse(uint8_t dutyCycle)
{
	  uint32_t val;
		val = (PWM_LOAD_VAL * (100-dutyCycle))/100;
	  // PF2 should be a digital input and PF3 must be a digital output. 
	  // PF3 is connected to the nSLEEP pin.
	  // You have to set this pin to a ‘1’ to make the motors move
		pwmConfig(PWM0_BASE,1,PWM_LOAD_VAL,val,val,PWM_CHANNEL_LOW,PWM_CHANNEL_PWM);
}


//*****************************************************************************
//*****************************************************************************
void  drv8833_rightForward(uint8_t dutyCycle)
{
		uint32_t val; 
		// getting cmpa and cmpb from the duty cycle 
		val = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(PWM1_BASE,1,PWM_LOAD_VAL,val,val,PWM_CHANNEL_PWM,PWM_CHANNEL_LOW);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_rightReverse(uint8_t dutyCycle)
{
		uint32_t val;
		val = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(PWM1_BASE,1,PWM_LOAD_VAL,val,val,PWM_CHANNEL_LOW,PWM_CHANNEL_PWM);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnLeft(uint8_t dutyCycle)
{
	 //just a combo of right forward and left rev
	 drv8833_rightForward(dutyCycle);
	 drv8833_leftReverse(dutyCycle);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnRight(uint8_t dutyCycle)
{
	 //combo of left turn forward and right reverse 
	 drv8833_leftForward(dutyCycle);
	 drv8833_rightReverse(dutyCycle);
}

// Implement halt function to cease left and right motors 
void	drv8833_halt()
{
  pwmConfig(PWM0_BASE, 1, PWM_LOAD_VAL, 0, 0, PWM_CHANNEL_LOW, PWM_CHANNEL_LOW);
  pwmConfig(PWM1_BASE, 1 , PWM_LOAD_VAL, 0, 0, PWM_CHANNEL_LOW,PWM_CHANNEL_LOW);
}
