#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123GH6PM.h"

#define PWM_GEN_ACTCMPBD_M         0x00000C00
#define PWM_GEN_ACTCMPBD_NOTHING   0x00000000
#define PWM_GEN_ACTCMPBD_INVERT    0x00000400
#define PWM_GEN_ACTCMPBD_LOW       0x00000800
#define PWM_GEN_ACTCMPBD_HIGH      0x00000C00

#define PWM_GEN_ACTCMPBU_M         0x00000300
#define PWM_GEN_ACTCMPBU_NOTHING   0x00000000
#define PWM_GEN_ACTCMPBU_INVERT    0x00000100
#define PWM_GEN_ACTCMPBU_LOW       0x00000200
#define PWM_GEN_ACTCMPBU_HIGH      0x00000300

#define PWM_GEN_ACTCMPAD_M         0x000000C0
#define PWM_GEN_ACTCMPAD_NOTHING   0x00000000
#define PWM_GEN_ACTCMPAD_INVERT    0x00000040
#define PWM_GEN_ACTCMPAD_LOW       0x00000080
#define PWM_GEN_ACTCMPAD_HIGH      0x000000C0

#define PWM_GEN_ACTCMPAU_M         0x00000030
#define PWM_GEN_ACTCMPAU_NOTHING   0x00000000
#define PWM_GEN_ACTCMPAU_INVERT    0x00000010
#define PWM_GEN_ACTCMPAU_LOW       0x00000020
#define PWM_GEN_ACTCMPAU_HIGH      0x00000030

#define PWM_GEN_ACTLOAD_M          0x0000000C
#define PWM_GEN_ACTLOAD_NOTHING    0x00000000
#define PWM_GEN_ACTLOAD_INVERT     0x00000004
#define PWM_GEN_ACTLOAD_LOW        0x00000008
#define PWM_GEN_ACTLOAD_HIGH       0x0000000C

#define PWM_GEN_ACTZERO_M          0x00000003
#define PWM_GEN_ACTZERO_NOTHING    0x00000000
#define PWM_GEN_ACTZERO_INVERT     0x00000001
#define PWM_GEN_ACTZERO_LOW        0x00000002
#define PWM_GEN_ACTZERO_HIGH       0x00000003


#define PWM_ENABLE_PWM0A          (1 << 0)
#define PWM_ENABLE_PWM0B          (1 << 1)
#define PWM_ENABLE_PWM1A          (1 << 2)
#define PWM_ENABLE_PWM1B          (1 << 3)
#define PWM_ENABLE_PWM2A          (1 << 4)
#define PWM_ENABLE_PWM2B          (1 << 5)
#define PWM_ENABLE_PWM3A          (1 << 6)
#define PWM_ENABLE_PWM3B          (1 << 7)

uint8_t pwmConfig(
  uint32_t base, 
  uint8_t pwm_generator, 
  uint32_t load, 
  uint32_t cmpa, 
  uint32_t cmpb,
  uint32_t gena,
  uint32_t genb
);
  
#endif