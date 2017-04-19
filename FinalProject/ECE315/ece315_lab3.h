#ifndef __ECE353_LAB3_H__
#define __ECE353_LAB3_H__

#include "../include/wireless.h"
#include "gpioPort.h"
#include "spi.h"
#include "wireless.h"
#include "boardUtil.h"

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the nordic wirless radio
//*****************************************************************************
#define   RF_GPIO_BASE        GPIOA_BASE
#define   RF_SPI_BASE         SSI0_BASE
#define   RF_CLK_PIN          PA2
#define   RF_MISO_PIN         PA4
#define   RF_MOSI_PIN         PA5

#define   RF_CLK_PIN_PCTL     GPIO_PCTL_PA2_SSI0CLK
#define   RF_MISO_PIN_PCTL    GPIO_PCTL_PA4_SSI0RX
#define   RF_MOSI_PIN_PCTL    GPIO_PCTL_PA5_SSI0TX

#define   RF_CS_BASE          GPIOA_BASE
#define   RF_CS_PIN           PA3

#define   RF_CE_GPIO_BASE     GPIOF_BASE
#define   RF_CE_PIN           PF4
#define   RF_CE_PERIH         GPIOF

#define   RF_IRQ_GPIO_BASE    GPIOD_BASE
#define   RF_IRQ_PIN          PD2

#define   RF_PAYLOAD_SIZE     0x04
#define   RF_CHANNEL          0x02


void rfInit(void);

#endif
