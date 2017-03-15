#include "ece353_lab3.h"

 static uint8_t ece353_ids[5]= {'3','5','3','0','0'};
 static uint8_t ece315_ids[5]= {'3','1','5','0','0'};
  
  
//*****************************************************************************
//*****************************************************************************
void rfInit(void)
{  
  wireless_set_pin_config(
    RF_SPI_BASE,
    RF_PAYLOAD_SIZE,
    RF_CHANNEL,
    RF_CS_BASE,
    RF_CS_PIN,
    RF_CE_GPIO_BASE,
    RF_CE_PIN
  );
  
  gpio_enable_port(RF_GPIO_BASE);
  
  // Configure SPI CLK
  gpio_config_digital_enable(  RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_alternate_function(    RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_port_control(     RF_GPIO_BASE, RF_CLK_PIN_PCTL);
  
  // Configure SPI MISO
  gpio_config_digital_enable(  RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_alternate_function(    RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_port_control(     RF_GPIO_BASE, RF_MISO_PIN_PCTL);
  
  // Configure SPI MOSI
  gpio_config_digital_enable(  RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_alternate_function(    RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_port_control(     RF_GPIO_BASE, RF_MOSI_PIN_PCTL);
  
  // Configure CS to be a normal GPIO pin that is controlled 
  // explicitly by software
  gpio_enable_port(RF_CS_BASE);
  gpio_config_digital_enable(  RF_CS_BASE,RF_CS_PIN);
  gpio_config_enable_output(    RF_CS_BASE,RF_CS_PIN);
  
  // Configure CE Pin as an output
  gpio_enable_port(RF_CE_GPIO_BASE);
  gpio_config_digital_enable(  RF_CE_GPIO_BASE,RF_CE_PIN);
  gpio_config_enable_output(    RF_CE_GPIO_BASE,RF_CE_PIN);
 
  
  initialize_spi( RF_SPI_BASE, 0);
  RF_CE_PERIH->DATA |= (1 << 1);
  
  wireless_configure_device(ece315_ids, ece353_ids ) ; 

}
