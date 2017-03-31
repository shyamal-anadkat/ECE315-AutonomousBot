#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../include/sysctrl.h"

#include "uart.h"
#include "gpioPort.h"
#include "pc_buffer.h"
#include "i2c.h"
#include "adc.h"
#include "interrupts.h"


#define NULL                0
#define UNUSED              0
#define DISABLED            0
#define NONE                0
#define PORT_CONTROL_DEFAULT 0 



#define PIN_0               (1 << 0)
#define PIN_1               (1 << 1)
#define PIN_2               (1 << 2)
#define PIN_3               (1 << 3)
#define PIN_4               (1 << 4)
#define PIN_5               (1 << 5)
#define PIN_6               (1 << 6)
#define PIN_7               (1 << 7)

#define     PA0     PIN_0
#define     PA1     PIN_1
#define     PA2     PIN_2
#define     PA3     PIN_3
#define     PA4     PIN_4
#define     PA5     PIN_5
#define     PA6     PIN_6
#define     PA7     PIN_7

#define     PB0     PIN_0
#define     PB1     PIN_1
#define     PB2     PIN_2
#define     PB3     PIN_3
#define     PB4     PIN_4
#define     PB5     PIN_5
#define     PB6     PIN_6
#define     PB7     PIN_7

#define     PC0     PIN_0
#define     PC1     PIN_1
#define     PC2     PIN_2
#define     PC3     PIN_3
#define     PC4     PIN_4
#define     PC5     PIN_5
#define     PC6     PIN_6
#define     PC7     PIN_7

#define     PD0     PIN_0
#define     PD1     PIN_1
#define     PD2     PIN_2
#define     PD3     PIN_3
#define     PD4     PIN_4
#define     PD5     PIN_5
#define     PD6     PIN_6
#define     PD7     PIN_7

#define     PE0     PIN_0
#define     PE1     PIN_1
#define     PE2     PIN_2
#define     PE3     PIN_3
#define     PE4     PIN_4
#define     PE5     PIN_5
#define     PE6     PIN_6
#define     PE7     PIN_7

#define     PF0     PIN_0
#define     PF1     PIN_1
#define     PF2     PIN_2
#define     PF3     PIN_3
#define     PF4     PIN_4
#define     PF5     PIN_5
#define     PF6     PIN_6
#define     PF7     PIN_7

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the serial debug UART
//*****************************************************************************
#define   SERIAL_DBG_BASE         GPIOA_BASE
#define   SERIAL_DBG_RX_PIN       PA0
#define   SERIAL_DBG_TX_PIN       PA1
#define   SERIAL_DBG_RX_PCTL      GPIO_PCTL_PA0_U0RX
#define   SERIAL_DBG_TX_PCTL      GPIO_PCTL_PA1_U0TX
#define   SERIAL_DEBUG_UART_BASE  UART0_BASE

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the I2C Bus
//*****************************************************************************
#define   EEPROM_GPIO_BASE         GPIOA_BASE
#define   EEPROM_I2C_BASE          I2C1_BASE
#define   EEPROM_I2C_SCL_PIN       PA6
#define   EEPROM_I2C_SDA_PIN       PA7
#define   EEPROM_I2C_SCL_PIN_PCTL  GPIO_PCTL_PA6_I2C1SCL
#define   EEPROM_I2C_SDA_PIN_PCTL  GPIO_PCTL_PA7_I2C1SDA

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the I2C Bus
//*****************************************************************************
#define   IO_EXPANDER_GPIO_BASE         GPIOA_BASE
#define   IO_EXPANDER_I2C_BASE          I2C1_BASE
#define   IO_EXPANDER_I2C_SCL_PIN       PA6
#define   IO_EXPANDER_I2C_SDA_PIN       PA7
#define   IO_EXPANDER_I2C_SCL_PIN_PCTL  GPIO_PCTL_PA6_I2C1SCL
#define   IO_EXPANDER_I2C_SDA_PIN_PCTL  GPIO_PCTL_PA7_I2C1SDA


#define TIVA_SONAR_RX (1 << 0)
#define TIVA_SONAR_TX (1 << 1)
#define SONAR_PW (1 << 2)
#define SONAR_AN (1 << 3)


void serialDebugInit(void);
void i2cInit(void);
void DisableInterrupts(void);
void EnableInterrupts(void);
void sensor_config(void);
void uart_init_9600(uint32_t , uint32_t , uint32_t);

#endif
