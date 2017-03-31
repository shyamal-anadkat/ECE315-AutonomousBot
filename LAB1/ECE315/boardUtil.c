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

//sensor config for sonar an, pw an tx !!
void sensor_config() {
	
	//for scope measurements 
	gpio_enable_port(GPIOF_BASE);
	gpio_config_enable_output(GPIOF_BASE, PF1);
	gpio_config_digital_enable( GPIOF_BASE, PF1);
	
	//SONAR_PW
	gpio_enable_port(GPIOE_BASE);
	gpio_config_enable_input(GPIOE_BASE, PE2);
  gpio_config_digital_enable( GPIOE_BASE, PE2);
  
	//SONAR_AN
	gpio_config_enable_input(GPIOE_BASE, PE3);
	gpio_config_analog_enable(GPIOE_BASE, PE3);
  gpio_config_alternate_function( GPIOE_BASE, PE3);
	
	//SONAR_TX
  gpio_config_digital_enable( GPIOE_BASE, PE0 | PE1);
  gpio_config_alternate_function( GPIOE_BASE, PE0 | PE1);
  gpio_config_port_control( GPIOE_BASE, GPIO_PCTL_PE0_U7RX | GPIO_PCTL_PE1_U7TX);
	
	uart_init_9600(UART7_BASE, SYSCTL_RCGCUART_R7, SYSCTL_PRUART_R7);

	NVIC_EnableIRQ(UART7_IRQn);
	NVIC_SetPriority(UART7_IRQn, 3);	
}


//************************************************************************
// Configure UART0 to be 9600, 8N1. 
//************************************************************************
void uart_init_9600(
  uint32_t base_addr, 
  uint32_t rcgc_mask, 
  uint32_t pr_mask
)
{
    UART0_Type *myUart;
    myUart = (UART0_Type *)base_addr;
    SYSCTL->RCGCUART |= rcgc_mask;
    
    while( (SYSCTL->PRUART & pr_mask) == 0)
    {}
    myUart->IBRD = 325;
    myUart->FBRD = 33;
    myUart->CTL &= ~UART_CTL_UARTEN;
    myUart->LCRH =   UART_LCRH_WLEN_8 | UART_LCRH_FEN;
    myUart->IFLS = UART_IFLS_RX2_8;  
		myUart->IM |= UART_IM_RXIM;
    myUart->CTL =  UART_CTL_RXE | UART_CTL_UARTEN;
}
