#ifndef __DRV8833_H__
#define __DRV8833_H__

#include "TM4C123GH6PM.h"
#include "boardUtil.h"
#include "pwm.h"

#define GPIO_PCTL_PE5_M1PWM3    0x00500000  // PWM2 PE5
#define GPIO_PCTL_PB4_M0PWM2    0x00040000  // PWM2 PB4
#define GPIO_PCTL_PB5_M0PWM3    0x00400000  // PWM3 PB5
#define GPIO_PCTL_PE4_M1PWM2    0x00050000  // PWM2 PE4


#define PWM_LOAD_VAL    10000
#define PWM_CHANNEL_PWM   (PWM_GEN_ACTCMPAD_LOW | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_LOW   (PWM_GEN_ACTCMPBD_LOW | PWM_GEN_ACTLOAD_LOW | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_HIGH  (PWM_GEN_ACTCMPBD_HIGH | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)

//***function declarations***
void  drv8833_gpioInit(void);
void  drv8833_leftForward(uint8_t dutyCycle);
void  drv8833_leftReverse(uint8_t dutyCycle);
void  drv8833_rightForward(uint8_t dutyCycle);
void  drv8833_rightReverse(uint8_t dutyCycle);
void  drv8833_turnLeft(uint8_t dutyCycle);
void  drv8833_turnRight(uint8_t dutyCycle);
void  drv8833_halt(void);
  
#endif
