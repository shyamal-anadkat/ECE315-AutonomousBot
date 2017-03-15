#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include <stdbool.h>

#include "boardUtil.h"

#define UNKNOWN 0

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the LCD Screen.
//
// Replace UNKNOWN with the correct pin and port information from the 
// robot schematic on the class website.
//*****************************************************************************
#define   LCD_GPIO_BASE       UNKNOWN
#define   LCD_SPI_BASE        UNKNOWN
#define   LCD_CLK_PIN         UNKNOWN
#define   LCD_CS_PIN          UNKNOWN
#define   LCD_MOSI_PIN        UNKNOWN

#define   LCD_CLK_PIN_PCTL    UNKNOWN
#define   LCD_CS_PIN_PCTL     UNKNOWN
#define   LCD_MOSI_PIN_PCTL   UNKNOWN


#define   GPIO_LCD_CD_BASE    UNKNOWN
#define   LCD_CD_PIN          UNKNOWN

#define   GPIO_LCD_RST_N_BASE UNKNOWN
#define   LCD_RST_N_PIN       UNKNOWN

//*****************************************************************************
// Initializes the pins needed to communicate with the LCD and issues the 
// initialization sequence found in the LCD datasheet via the SPI interface
//*****************************************************************************
void ece315_lcdInit(void);

 //****************************************************************************
// Sets the currently active page
//*****************************************************************************
void ece315_lcdSetPage(uint8_t   page);
  
//*****************************************************************************
// Sets the currently active column
//*****************************************************************************
void ece315_lcdSetColumn(uint8_t   column);
  
//*****************************************************************************
// Writes 8-bits of data to the current column of the LCD
//*****************************************************************************
void ece315_lcdWriteData(uint8_t   data);
  
//*****************************************************************************
// Erases the LCD screen.
//*****************************************************************************
void ece315_lcdClear(void);

//*****************************************************************************
// Each character is 10 columns wide.  The colStart is the column number where
// the first column will be printed.
//
// font.c contains a lookup table for printing out characters to the LCD screen.
// You should note that each character is 16 pixels high and 10 pixels wide.
// For each character, you will have to write to two different pages to print
// out a single character.  
//*****************************************************************************
 void ece315_lcdWriteChar( uint8_t page, char c, uint8_t colStart);
 
//*****************************************************************************
// Write a string of characters out to the LCD screen.  Only the first 
// 10 characters will be printed.  The function will also terminate when
// a null character is encountered.
//*****************************************************************************
  void ece315_lcdWriteString( uint8_t line, char *string);
  
#endif
