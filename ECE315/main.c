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

//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#include "TM4C123.h"
#include "boardUtil.h"
#include "adc.h"



//*****************************************************************************
// Global Variables
//*****************************************************************************

  
//*****************************************************************************
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
  SysTick_Config(2500);
  sonar_config_gpio();
	serialDebugInit();
  EnableInterrupts();
}


//*****************************************************************************
//*****************************************************************************

extern bool measureAnalog;
extern bool measureDigital;
int main(void)
{
  int displaycount = 0; 
  int analogvalue = 0;
  int digitalvalue = 0;
  char a, b, c;
	char left[3];
	char out[15];

  initializeBoard();

  uartTxPoll(UART0_BASE, "\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  uartTxPoll(UART0_BASE,"* ECE315 Default Project\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  			 
  
  while(1)
  {
	  	if(measureDigital){
				if(GPIOE->DATA != 0) {
					counthigh++;
				}
				else if (counthigh != 0 && GPIOE->DATA == 0) {
					digitalvalue = (counthigh*50)/(147);
				}
				else { 
					counthigh = 0; 
				}
		}
		if(measureAnalog){
			analogvalue = getADCValue(ADC0_BASE,0) / 7;
			measureAnalog = false; 
			displaycount = (displaycount + 1) % 100;
		}
	  	
	  if(uartRxPoll(UART7_BASE, true) == 'R') {
			a = uartRxPoll(UART7_BASE, true);
			b = uartRxPoll(UART7_BASE, true);
			c = uartRxPoll(UART7_BASE, true);
			left[2] = c;
			left[1] = b;
			left[0] = a;
		}
	  
		
		
		if(displaycount == 99) {
			uartTxPoll(UART0_BASE, "\n\rRight (Digital):\n\r");
			sprintf(out, "%d", digitalvalue);
			uartTxPoll(UART0_BASE, out);
			uartTxPoll(UART0_BASE, "\n\rMiddle (Analog):\n\r");
			sprintf(out, "%d", analogvalue);
			uartTxPoll(UART0_BASE,  out);
			uartTxPoll(UART0_BASE, "\n\rLeft (Polling):\n\r");
			uartTxPoll(UART0_BASE,  left);
			
		}
	}
  
}

