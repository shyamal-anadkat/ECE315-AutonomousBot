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

#define GPIOA_P6 (*((volatile unsigned long *)0x40004100))

//*****************************************************************************
// Global Variables
//*****************************************************************************

volatile bool AlertSysTick; 
volatile bool Alert10ms; 
volatile bool Alert1s;   
char console[50];
volatile char leftBuf[4];

  
//*****************************************************************************
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
  serialDebugInit();
  EnableInterrupts();
	sensor_config();
	initializeADC(ADC0_BASE);
	//every 50us
	SysTick_Config(2500);
}

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	uint32_t analogVal, digitalDist, pw, pb;
	
	uint8_t high1, high2;	
	pw = 0;
  initializeBoard();


  uartTxPoll(UART0_BASE, "\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  uartTxPoll(UART0_BASE,"* ---ECE315 Default Project---\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
	
  while(1)
  {

		//get analog value every 10ms
		//center sensor reading
		if(Alert10ms){
			
			//for scope measurements
			if((GPIOF->DATA & PF1) == 0x2){
					GPIOF->DATA &= ~0x2;
				}	
				else{
					GPIOF->DATA |= 0x2;
				}
				
			analogVal = ((getADCValue( ADC0_BASE , 0)) * 3.3 / (0.0064 * 0xFFF)); // 9.8 : 5; 6.4 : 3.3
			Alert10ms = false;
		}
		
		//detect pulse width 
		//right sensor
		
		if(AlertSysTick){

			high2 = high1;
			high1 = ((GPIOE->DATA & SONAR_PW) >> 2);
			
			if(high1 && !high2){
				pw = 50;
			}
			else if(high1 && high2){
				pw = pw + 50;
			}
			else if(!high1 && high2){
				digitalDist = pw / 147;
				pw = 0;
			}
			else{
				pw = 0;
			}
			AlertSysTick = false;
		}
		
		//print to console every 1s 
		if(Alert1s){
			Alert1s = false;
		
			sprintf(console, "-x-x-x-x-x-x- Shyamal, Sneha, Jamie -x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\r");
			uartTxPoll(UART0_BASE, console);

			sprintf(console, "Right (digital) :  %d\n\r", digitalDist);
			uartTxPoll(UART0_BASE, console);
			
			sprintf(console, "Center (analog): %d\n\r", analogVal);
			uartTxPoll(UART0_BASE, console);
	
			sprintf(console, "Left (polling) : %s\n\r", leftBuf);
			uartTxPoll(UART0_BASE, console);
		}
  }
}
