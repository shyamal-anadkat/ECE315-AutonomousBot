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
#include "led_controller.h"
#include "encoders.h"


//*****************************************************************************
// Global Variables
//*****************************************************************************
char console[50]; //for console debug 

volatile bool AlertSysTick; 
volatile bool Alert10msA; 
volatile bool Alert10msB;
volatile bool Alert30ms; 
volatile bool Alert1sA;
volatile bool Alert1sB; 
extern uint32_t leftA_pulse;

char leftBuf[4];	//for left sonar sensor dist
float left_sensor_readings[5];	// used to get average reading over 5 cycles
float center_sensor_readings[5];
uint32_t right_sensor_readings[5];
float left_sensor;  	//format distance data
float center_sensor;
uint32_t right_sensor;
uint32_t inches;
//typedef enum {RIGHT};
  
//*****************************************************************************
// INITIALIZE BOARD AND HARDWARE 
//*****************************************************************************
void initializeBoard(void)
{
  DisableInterrupts();
	SysTick_Config(2500);
  serialDebugInit();	//serial-debug initialization
	ece315_lcdInit();   //lcd-init
	drv8833_gpioInit(); //motors init
	rfInit();      		 	//RF-initialization
	encodersInit(); 		//init encoders
	sensor_config();		//sensor-config
	initializeADC(ADC0_BASE);	//init ADC0 base
	ledController_init(IO_I2C_BASE);
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
	uint16_t slow_speed;
	uint16_t medium_speed;
	uint16_t fast_speed;
	int i;
	uint32_t pw = 0;
	uint32_t temp = 0;
  uint32_t temp1 = 0;
	uint8_t high1, high2;	
	bool right_turn = false;
	uint8_t left_count = 0;
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
		if(Alert1sA){
			memset (msg,0,80);
			inches = pulse_to_inches(leftA_pulse);
			sprintf(msg,"Dist: %i", inches);
			ece315_lcdWriteString(0, msg);
			Alert1sA = false;
		}
		
		// update center sensor
		if(Alert10msA){
			center_sensor_readings[4] = center_sensor_readings[3];
			center_sensor_readings[3] = center_sensor_readings[2];
			center_sensor_readings[2] = center_sensor_readings[1];
			center_sensor_readings[1] = center_sensor_readings[0];
			center_sensor_readings[0] = ((getADCValue( ADC0_BASE , 0)) * 3.3 / (0.0064 * 0xFFF)); // 9.8 : 5; 6.4 : 3.3
			center_sensor = (center_sensor_readings[4] + center_sensor_readings[3] + center_sensor_readings[2] + center_sensor_readings[1] + center_sensor_readings[0]) / 5;
			Alert10msA = false;
		}
		
		// update left sensor
		left_sensor_readings[4] = left_sensor_readings[3];
		left_sensor_readings[3] = left_sensor_readings[2];
		left_sensor_readings[2] = left_sensor_readings[1];
		left_sensor_readings[1] = left_sensor_readings[0];
		left_sensor_readings[0] = (float)atof(leftBuf);
		left_sensor = (left_sensor_readings[4] + left_sensor_readings[3] + left_sensor_readings[2] + left_sensor_readings[1] + left_sensor_readings[0]) / 5;
		
		//detect pulse width 
		//right sensor
		
		// NOT USING RIGHT SENSOR FOR NOW
		/*if(AlertSysTick){
			high2 = high1;
			high1 = ((GPIOE->DATA & SONAR_PW) >> 2);
			
			if(high1 && !high2){
				pw = 50;
			}
			else if(high1 && high2){
				pw = pw + 50;
			}
			else if(!high1 && high2){
						right_sensor_readings[4] = right_sensor_readings[3];
						right_sensor_readings[3] = right_sensor_readings[2];
						right_sensor_readings[2] = right_sensor_readings[1];
						right_sensor_readings[1] = right_sensor_readings[0];
						right_sensor_readings[0] = (pw / 147);
						temp = (pw >> 7);
						right_sensor = (right_sensor_readings[4] + right_sensor_readings[3] + right_sensor_readings[2] + right_sensor_readings[1] + right_sensor_readings[0]) / 5;
						//right_sensor_readings[0] = pw / 147;
						pw = 0;
			}
			else{
						pw = 0;
			}
			AlertSysTick = false;
		}*/
		
		memset (msg,0,100);
		//if(temp>250) {
		sprintf(msg,"Left: %f, Center: %f, right: %d\n\r",left_sensor, center_sensor, temp);
		//}
	
			
	 uartTxPoll(UART0_BASE, msg);
		
		slow_speed = 0x3F;
		medium_speed = 0x7F;
		fast_speed = 0xFF;
		
		
	
		
		// RIGHT SENSOR
		 /*
		 if(right_sensor < 8) {
				//RED LED
			led_controller_byte_write(IO_I2C_BASE, 0x0D, 0xFF);
			led_controller_byte_write(IO_I2C_BASE, 0x0E, 0x00);
			led_controller_byte_write(IO_I2C_BASE, 0x0F, 0x00);
			
				// Write all the configureation data to the registers
			led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
				
			}
			
			if(right_sensor > 8 & right_sensor < 15) {
				
			//YELLOW LED
			led_controller_byte_write(IO_I2C_BASE, 0x0D, 0xFF);
			led_controller_byte_write(IO_I2C_BASE, 0x0E, 0xFF);
			led_controller_byte_write(IO_I2C_BASE, 0x0F, 0x00);
			
			// Write all the configureation data to the registers
			led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
			}
				
			if(right_sensor > 15) {
				
			//GREEN LED
			led_controller_byte_write(IO_I2C_BASE, 0x0D, 0x00);
			led_controller_byte_write(IO_I2C_BASE, 0x0E, 0xFF);
			led_controller_byte_write(IO_I2C_BASE, 0x0F, 0x00);
				
			// Write all the configureation data to the registers
			led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);	
			} */
		
		

		
		
		
		if(Alert30ms){
			//DisableInterrupts();
	
	 //****LED CONTROLLER*****//
	 if(left_sensor < 8) {
			//RED LED
		 ledController_init(IO_I2C_BASE);
		led_controller_byte_write(IO_I2C_BASE, 0x07, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x08, 0x00);
		led_controller_byte_write(IO_I2C_BASE, 0x09, 0x00);
		
			// Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
			
		}
		
		if(left_sensor > 8 & left_sensor < 15) {
			ledController_init(IO_I2C_BASE);
		//YELLOW LED
		led_controller_byte_write(IO_I2C_BASE, 0x07, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x08, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x09, 0x00);
		
		// Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
		}
			
		if(left_sensor > 15) {
			ledController_init(IO_I2C_BASE);
		//GREEN LED
		led_controller_byte_write(IO_I2C_BASE, 0x07, 0x00);
		led_controller_byte_write(IO_I2C_BASE, 0x08, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x09, 0x00);
			
	  // Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);	
		}
			
		
			
		//CENTER SENSOR
	 if(center_sensor < 8) {
			//RED LED
		led_controller_byte_write(IO_I2C_BASE, 0x0A, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x0B, 0x00);
		led_controller_byte_write(IO_I2C_BASE, 0x0C, 0x00);
		
			// Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
			
		}
		
		if(center_sensor > 8 & center_sensor < 15) {
			
		//YELLOW LED
		led_controller_byte_write(IO_I2C_BASE, 0x0A, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x0B, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x0C, 0x00);
		
		// Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);
		}
			
		if(center_sensor > 15) {
			
		//GREEN LED
		led_controller_byte_write(IO_I2C_BASE, 0x0A, 0x00);
		led_controller_byte_write(IO_I2C_BASE, 0x0B, 0xFF);
		led_controller_byte_write(IO_I2C_BASE, 0x0C, 0x00);
			
	  // Write all the configureation data to the registers
    led_controller_byte_write(IO_I2C_BASE, 0x10, 0x00);	
		}


			//drv8833_halt();
			if((left_sensor >= 9 && left_sensor <= 11) || right_turn){
				if(center_sensor < 7 && ~right_turn) {
						// Wall to the left and ahead -> Turn Right
						drv8833_leftForward(slow_speed);
						drv8833_rightReverse(slow_speed);
						right_turn = true;	// When asserted, turn right until center sensor doesn't see wall
				} else if(center_sensor < 9) {
						// Wall to the left and ahead -> Turn Right
						drv8833_leftForward(slow_speed);
						drv8833_rightReverse(slow_speed);
						right_turn = true;	// When asserted, turn right until center sensor doesn't see wall
				} else {
						// Wall to the left -> Drive Straight
						drv8833_leftForward(slow_speed);
						drv8833_rightForward(slow_speed);
						right_turn = false;
				}
			} else if(left_sensor > 15){
						// Drifting Right -> Turn Left
						left_count = (left_count + 1) % 8;
						if(left_count < 3) {
							drv8833_leftReverse(fast_speed);
							drv8833_rightForward(fast_speed); 
						} else {
						drv8833_leftForward(slow_speed);
						drv8833_rightForward(slow_speed);
						}
			} else if(left_sensor > 11){
						// Drifting Right -> Turn Left
						drv8833_leftReverse(slow_speed);
						drv8833_rightForward(slow_speed);
			} else {
						// Drifting Left -> Turn Right
						drv8833_leftForward(slow_speed);
						drv8833_rightReverse(slow_speed);
			}
			Alert30ms = false;
			//EnableInterrupts();
		}
		
			
		
	}
}
