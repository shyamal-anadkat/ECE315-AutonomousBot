#include "lcd.h"
#include "../include/spi.h"
#include "fonts.h"


//*****************************************************************************
// Initializes the pins needed to communicate with the LCD and issues the 
// initialization sequence found in the LCD datasheet via the SPI interface
//*****************************************************************************
void ece315_lcdInit(void)
{
	//GPIOA_Type  *gpioResetPtr;
  GPIOA_Type  *gpioCmdPtr = (GPIOA_Type *) GPIOD_BASE;
	uint8_t tx_data, rx_data;
	
	gpio_enable_port(LCD_GPIO_BASE);
	
  // Configure SPI CLK
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CLK_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CLK_PIN_PCTL);
    
  // Configure SPI CS
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_CS_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_CS_PIN_PCTL);

  // Configure SPI MOSI
  gpio_config_digital_enable(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_alternate_function(LCD_GPIO_BASE, LCD_MOSI_PIN);
  gpio_config_port_control(LCD_GPIO_BASE, LCD_MOSI_PIN_PCTL);
  
  // Configure CD
  gpio_config_digital_enable(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  gpio_config_enable_output(GPIO_LCD_CD_BASE,LCD_CD_PIN);
  
  // Configure RST_N
  gpio_config_digital_enable(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
  gpio_config_enable_output(GPIO_LCD_RST_N_BASE, LCD_RST_N_PIN);
  
  initialize_spi( LCD_SPI_BASE, 3);
  	
		
	//****LCD INIT -- LAB 4*** 

  // Bring the LCD out of reset
	gpioCmdPtr->DATA |= PD6;
  
  // Use spiTx() from the ece315 driver library to issue the sequence of 
  // commands in the LCD data sheet to initialize the LCD.  
	// ece315_lcdClear();
	//Enter Command Mode
  gpioCmdPtr->DATA &= ~LCD_CD_PIN  ;
 
	//Set Scroll Line
  tx_data = 0x40;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set SEG Directions
  tx_data = 0xA1;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set COM direction
  tx_data = 0xC0;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set All Pixel on
  tx_data = 0xA4;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set Inverse Display
  tx_data = 0xA6;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set LCD Bias Ratio
  tx_data = 0xA2;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set Power Control
  tx_data = 0x2F;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set VLCD Resistor Ratio
  tx_data = 0x27;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set Electronic Volume
  tx_data = 0x81;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
	
  tx_data = 0x10;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set Adv Program Control
  tx_data = 0xFA;
  spiTx(SSI3_BASE, &tx_data, 1, &rx_data);
	
  tx_data = 0x90;
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
  
  //Set Display Enable
  tx_data = 0xAF;
	
  spiTx(SSI3_BASE,&tx_data, 1, &rx_data);
	

  //Exit Command Mode
  gpioCmdPtr->DATA |=  LCD_CD_PIN;
	
	ece315_lcdClear();
}

 //****************************************************************************
// Sets the currently active page
//*****************************************************************************
  void ece315_lcdSetPage(uint8_t   page)
  {
		uint8_t tx_data;
		uint8_t rx_data;
		
		// Set CD to 0
		GPIOD->DATA &= ~PD7;
	
		// Send 1011XXXX, where Xs are page address
		tx_data = 0xB0 | (0x0F & page);
    spiTx(LCD_SPI_BASE, &tx_data, 1, &rx_data);
		
		// Reset CD to 1
		GPIOD->DATA |= PD7;
  }
  
//*****************************************************************************
// Sets the currently active column
//*****************************************************************************
void ece315_lcdSetColumn(uint8_t   column)
{
  	uint8_t tx_data;
		uint8_t rx_data;
		
		// Set CD to 0
		GPIOD->DATA &= ~PD7;
	
		// Send 0000 yyyy where yyyy is the least significant 4 bits of column number
		tx_data = column & 0x0F;
    spiTx(LCD_SPI_BASE, &tx_data, 1, &rx_data);
		
		// Send 0001 yyyy where yyyy is the most significant 4 bits of column number
		tx_data = 0x1F & (column >> 4);
    spiTx(LCD_SPI_BASE, &tx_data, 1, &rx_data);
	
		// Reset CD to 1
		GPIOD->DATA |= PD7;
}
  
//*****************************************************************************
// Writes 8-bits of data to the current column of the LCD
//*****************************************************************************
  void ece315_lcdWriteData(uint8_t   data)
  {
		uint8_t rx_data;
		//GPIOD->DATA |= PD7;
		spiTx(LCD_SPI_BASE, &data, 1, &rx_data);
  }
  
//*****************************************************************************
// Erases the LCD screen.
//*****************************************************************************
 void ece315_lcdClear(void)
 {
		int page;
	  int column;
		for(page = 0; page < 8; page++){
			ece315_lcdSetPage(page);
			for(column = 0; column < 102; column++){
				ece315_lcdSetColumn(column);
				ece315_lcdWriteData(0x00);
			}
		}
	 
 }

//*****************************************************************************
// Each character is 10 columns wide.  The colStart is the column number where
// the first column will be printed.
//
// font.c contains a lookup table for printing out characters to the LCD screen.
// You should note that each character is 16 pixels high and 10 pixels wide.
// For each character, you will have to write to two different pages to print
// out a single character.  
//*****************************************************************************
void ece315_lcdWriteChar( uint8_t page, char c, uint8_t colStart)
 {
	 int i, j;
   ece315_lcdSetPage(page);
	 for(i = colStart; i < colStart+10; i++){
		 ece315_lcdSetColumn(i);
		 ece315_lcdWriteData(courierNew_10ptBitmaps[(30+c)*20]);
	 }
	 ece315_lcdSetPage(page + 1);
	 for(j = colStart; j < colStart+10; j++){
		 ece315_lcdSetColumn(j);
		 ece315_lcdWriteData(courierNew_10ptBitmaps[(30+c)*20 + 10]);
	 }
 }
 
//*****************************************************************************
// Write a string of characters out to the LCD screen.  Only the first 
// 10 characters will be printed.  The function will also terminate when
// a null character is encountered.
//*****************************************************************************
void ece315_lcdWriteString( uint8_t line, char *string)
{
	int i;
  for(i = 0; i < 10; i++){
		if(string == '\0')
			return;
		ece315_lcdWriteChar( line * 2, string[i], 10*i);
	}
}  

