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

//***Include headers***//
#include "lcd.h"
#include "TM4C123.h"
#include "boardUtil.h"
#include "ece315_lab3.h"
#include "drv8833.h"
#include "adc.h"


//*****************************************************************************
// Global Variables
//*****************************************************************************
char console[50]; //for console debug 
char leftBuf[4];	//for left sonar sensor dist
float distdata;  	//format distance data
  
//*****************************************************************************
// INITIALIZE BOARD AND HARDWARE 
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
	
  serialDebugInit();	//serial-debug initialization
	ece315_lcdInit();   //lcd-init
	drv8833_gpioInit(); //motors init
	rfInit();      		 	//RF-initialization
	encodersInit(); 		//init encoders
	sensor_config();		//sensor-config
	initializeADC(ADC0_BASE);	//init ADC0 base
	
  EnableInterrupts();
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	//****VARIABLES******//
	char msg[80];
	char dist[6];
	wireless_com_status_t status;
	uint32_t data;
	uint8_t char1, char2;
	uint16_t speed;
	int i;
	dist[0] = 'D';
	dist[1] = 'I';
	dist[2] = 'S';
	dist[3] = 'T';
	dist[4] = ':';
	dist[5] = ' ';
	//******************//
  
	
	// Init hardware and peripherals 
  initializeBoard();

  uartTxPoll(UART0_BASE, "\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  uartTxPoll(UART0_BASE,"* ECE315 Lab 4 - Sneha, Shyamal, Jamie\n\r");
  uartTxPoll(UART0_BASE,"**************************************\n\r");
  
  while(1)
  {
		// Check to see when wireless data arrives
		status = wireless_get_32(false, &data);
		
		if(status == NRF24L01_RX_SUCCESS)   //success status 
		{
			memset (msg,0,80);
			sprintf(msg,"Data RXed: %c%c %d\n\r", data>>24, data >> 16, data & 0xFFFF);
			
			uartTxPoll(UART0_BASE, msg);
			uartTxPoll(UART0_BASE, msg);
			
			char1 = (data>>24) & 0xFF;   //Bits 31-24 : DIRECTION
			
			char2 = (data>>16) & 0xFF;	 //Bits 23-16 
			
			speed = data & 0xFFFF;       //lower 16 bits: DUTY CYCLE
			
			if(char1=='F' & char2 == 'W' )
			{
				// Forward
				ece315_lcdWriteString(1, "DIR: FWD"); 		//print out the direction data 
				drv8833_leftForward(speed);
				drv8833_rightForward(speed);
			}
			else if(char1=='R' & char2 == 'V')
			{
				// Reverse
				ece315_lcdWriteString(1, "DIR: REV");			//print the reverse direction data
				drv8833_leftReverse(speed);
				drv8833_rightReverse(speed);
			}
			else if(char1=='R' & char2 == 'T')
			{
				// Right
				ece315_lcdWriteString(1, "DIR: TURN");
				drv8833_turnRight(speed);
			}
			else if(char1=='L' & char2 == 'F')
			{
				// Left
				ece315_lcdWriteString(1, "DIR: TURN");
				drv8833_turnLeft(speed);
			}
			else if(char1=='S' & char2 == 'T')
			{
				// Stop
				ece315_lcdWriteString(1, "DIR: STOP");
				drv8833_halt();
			}
			else
			{
				// Command not recongized, just halt!
				ece315_lcdWriteString(1, "DIR: STOP");
				drv8833_halt();
			}
  }
		
		// prints out distance data in float pointer format 
		distdata = (float)atof(leftBuf);
		sprintf((dist + 6), "%f", distdata);
		ece315_lcdWriteString(0, dist);
		
		// prints out the dist data to debug
		sprintf(console, "Left (polling) : %s\n\r", leftBuf);
		uartTxPoll(UART0_BASE, console);
		// ece315_lcdClear();
	}
}
