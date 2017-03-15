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



//************************************************************************
// Configure a UART to be 9600, 8N1.  
//************************************************************************
bool uart_init_lab1(uint32_t uart_base, bool enable_rx_irq, bool enable_tx_irq) {
	
    UART0_Type *uart = (UART0_Type *)(uart_base);
	  uint32_t rcgc_mask;
    uint32_t pr_mask;
    
    if (verify_uart_base(uart_base) == false)
    {
      return false;
    }
		rcgc_mask = uart_get_rcgc_mask(uart_base);
    pr_mask = uart_get_pr_mask(uart_base);
		
		// Turn the clock on using the rcgc_mask
	  SYSCTL->RCGCUART|= rcgc_mask; 

    // Wait for the PRUART to indicate the port is ready
		while( (SYSCTL->PRUART  & pr_mask) == 0) 
		{}	
			
		//Disable the UART (CTL)
    uart->CTL &= ~UART_CTL_UARTEN;
			
		//set the baud rate to be 9600.
		uart->IBRD = 325;
		uart->FBRD = 33; 
			
		uart->LCRH |= UART_LCRH_FEN;    //enable FIFO
		uart->LCRH |= UART_LCRH_WLEN_8;
		
	  //enable uart stuff 
		uart->CTL = (UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN);
	
}

void sonar_config_gpio(void)
{
	//J7
	gpio_enable_port(GPIOE_BASE);
  gpio_config_digital_enable( GPIOE_BASE, PE2);
	
	//J11
	initializeADC(ADC0_BASE);
	gpio_config_analog_enable(GPIOE_BASE, PE3);
	
	//J8
	gpio_config_digital_enable( GPIOE_BASE, PE0 | PE1);
	gpio_config_alternate_function( GPIOE_BASE, PE0 | PE1);
	gpio_config_port_control( GPIOE_BASE, GPIO_PCTL_PE0_U0RX | GPIO_PCTL_PE1_U0TX);
	
}

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

void sonarInit(void){
	
	// Configure GPIO Pins
	sonar_config_gpio();
	
}



/****************************************************************************
 * HELPER FUNCTIONS
 ****************************************************************************/


/****************************************************************************
 * Verify that the uart base address is valid
 ****************************************************************************/
bool verify_uart_base(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     case UART1_BASE:
     case UART2_BASE:
     case UART3_BASE:
     case UART4_BASE:
     case UART5_BASE:
     case UART6_BASE:
     case UART7_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}



/****************************************************************************
 * Return the RCGC Mask
 ****************************************************************************/
uint32_t uart_get_rcgc_mask(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return SYSCTL_RCGCUART_R0;
     }
     case UART1_BASE:
     {
       return SYSCTL_RCGCUART_R1;
     }
     case UART2_BASE:
     {
        return SYSCTL_RCGCUART_R2;
     }
     case UART3_BASE:
     {
       return SYSCTL_RCGCUART_R3;
     }
     case UART4_BASE:
     {
       return SYSCTL_RCGCUART_R4;
     }
     case UART5_BASE:
     {
       return SYSCTL_RCGCUART_R5;
     }
     case UART6_BASE:
     {
       return SYSCTL_RCGCUART_R6;
     }
     case UART7_BASE:
     {
       return SYSCTL_RCGCUART_R7;
     }
     default:
     {
       return 0;
     }
   }
}


/****************************************************************************
 * Return the RCGC Mask
 ****************************************************************************/
uint32_t uart_get_pr_mask(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return SYSCTL_PRUART_R0;
     }
     case UART1_BASE:
     {
       return SYSCTL_PRUART_R1;
     }
     case UART2_BASE:
     {
        return SYSCTL_PRUART_R2;
     }
     case UART3_BASE:
     {
       return SYSCTL_PRUART_R3;
     }
     case UART4_BASE:
     {
       return SYSCTL_PRUART_R4;
     }
     case UART5_BASE:
     {
       return SYSCTL_PRUART_R5;
     }
     case UART6_BASE:
     {
       return SYSCTL_PRUART_R6;
     }
     case UART7_BASE:
     {
       return SYSCTL_PRUART_R7;
     }
     default:
     {
       return 0;
     }
   }
}



/****************************************************************************
 * Return the IRQ Number
 ****************************************************************************/
IRQn_Type uart_get_irq_num(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return UART0_IRQn;
     }
     case UART1_BASE:
     {
       return UART1_IRQn;
     }
     case UART2_BASE:
     {
        return UART2_IRQn;
     }
     case UART3_BASE:
     {
       return UART3_IRQn;
     }
     case UART4_BASE:
     {
       return UART4_IRQn;
     }
     case UART5_BASE:
     {
       return UART5_IRQn;
     }
     case UART6_BASE:
     {
       return UART6_IRQn;
     }
     case UART7_BASE:
     {
       return UART7_IRQn;
     }
     default:
     {
       return 0;
     }
   }
}
