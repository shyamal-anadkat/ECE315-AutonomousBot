// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "TM4C123GH6PM.h"
#include "boardUtil.h"
#include "../include/sysctrl.h"



void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

// TODO
// FOR LAB 4 : 

/*There are three MaxBotix range finders found on the ECE315 robot platform. One of the sensors (J8 or the left facing sensor)
measures the distance and outputs the distance information serially via the UART interface. You will need to configure the
GPIO pins connected to TIVA_SONAR_TX and TIVA_SONAR_RX as digital pins with alternate function behavior
corresponding to UART.
In order to initialize the UART peripheral, follow the same implementation as that of serialDebugInit() defined within
boardUtil.c and boardUtil.h. Notice how a struct has been defined with the UART’s base address and passed as
argument to the init function. Some of the high-level steps for interfacing are as follows:
*/


// 1) Initialize the corresponding UART peripheral in boardUtil.c
// 2) Enable UART RX interrupt





//*****************************************************************************
// Configure PA0 and PA1 to be UART pins
//*****************************************************************************
void uart0_config_gpio(void)
{
   gpio_enable_port(GPIOA_BASE);
   gpio_config_digital_enable( GPIOA_BASE, PA0 | PA1);
   gpio_config_alternate_function( GPIOA_BASE, PA0 | PA1);
   gpio_config_port_control( GPIOA_BASE, GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
}

//*****************************************************************************
//*****************************************************************************
void serialDebugInit(void)
{
  // Configure GPIO Pins
  uart0_config_gpio();
 
  
  // Initialize UART0 for 8N1, interrupts enabled.
  uart_init_115K(
    UART0_BASE, 
    SYSCTL_RCGCUART_R0, 
    SYSCTL_PRUART_R0
  );
}
