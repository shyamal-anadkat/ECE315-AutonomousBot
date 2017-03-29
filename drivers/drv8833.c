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
  
  // Configure PF2 as a digital input
  
  // Configure PF3 as a digital output and set it to 1
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
