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
  serialDebugInit();
  SysTick_Config(2500);
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

  initializeBoard();

  uartTxPoll(UART0_BASE, "\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  uartTxPoll(UART0_BASE,"* ECE315 Default Project\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  			 
  
  while(1)
  {
	  	if(measureDigital){
			digitalvalue = (UART7->PE2)*(147*10^-6);	// 147uS per inch
			measureDigital = false;
		}
		if(measureAnalog){
			analogvalue = getADCValue(ADC0_BASE,0 );
			measureAnalog = false; 
			displaycount = (displaycount + 1) % 100;
		}
	  	
	  	if(uartRxPoll(UART0_BASE, true) == 'R') {
			a = uartRxPoll(UART7_BASE, true);
			b = uartRxPoll(UART7_BASE, true);
			c = uartRxPoll(UART7_BASE, true);
			
		}
	  
		if(displaycount == 99) {
			uartTxPoll(UART7_BASE, "Right (Digital):\n");
			uartTxPoll(UART7_BASE, digitalvalue);
			uartTxPoll(UART7_BASE, "Middle (Analog):\n");
			uartTxPoll(UART7_BASE, analogvalue);
			uartTxPoll(UART7_BASE, "Left (Polling):\n");
			uartTxPoll(UART7_BASE, strcat(strcat(c, b), a)); 
		}
	}
  }
}

