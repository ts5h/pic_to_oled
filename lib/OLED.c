/*
* Project Name: OLED_I2C
* File: OLED.c
* Description: OLED 128X32 SSD1306  I2C library c file
* Author: Gavin Lyons.
* Complier: xc8 v2.00 compiler
* PIC: PIC16F1619 
* IDE:  MPLAB X v5.00
* Development board: Microchip Curiosity Board, PIC16F1619
* Created March 2019
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_16F1619_projects
*/

/*
 * Modified August 2022
 * PIC: PIC16F1705
 * IDE: MPLAB X v6.00
 */

#include "../mcc_generated_files/mcc.h"
#include "../mcc_generated_files/examples/i2c_master_example.h"
#include "OLED.h"         
#include "font.h"

// Function to Send command byte to OLED, passed byte
void OLED_Command(uint8_t command)
{
  uint8_t data_I2C[2];
  
  data_I2C[0] = SSD1306_COMMAND; 
  data_I2C[1] = command;

 
  I2C_WriteNBytes(SSD1306_ADDR, data_I2C, 2);
}

// Function to Send data byte to OLED, passed byte
void OLED_Data(uint8_t value)
{
  uint8_t data_I2C[2];
  
  data_I2C[0] = SSD1306_DATA_CONTINUE; 
  data_I2C[1] = value; 
  

  I2C_WriteNBytes(SSD1306_ADDR, data_I2C, 2);
}

// Function to initialize OLED
void OLED_Init(void)
{
    OLED_Command(SSD1306_DISPLAY_OFF);
    OLED_Command(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    OLED_Command(0x80);
    OLED_Command(SSD1306_SET_MULTIPLEX_RATIO);
    OLED_Command(SSD1306_LCDHEIGHT - 1 );
    OLED_Command(SSD1306_SET_DISPLAY_OFFSET);
    OLED_Command(0x00);
    OLED_Command(SSD1306_SET_START_LINE | 0x00);  // Line: 0
    OLED_Command(SSD1306_CHARGE_PUMP);
    OLED_Command(0x14);
    OLED_Command(SSD1306_MEMORY_ADDR_MODE);
    OLED_Command(0x00);  //Hor Addressing Mode is Used (02 is Ver)
    OLED_Command(SSD1306_SET_SEGMENT_REMAP | 0x01);
    OLED_Command(SSD1306_COM_SCAN_DIR_DEC);
    OLED_Command(SSD1306_SET_COM_PINS);
    OLED_Command(0x02);
    OLED_Command(SSD1306_SET_CONTRAST_CONTROL);
    OLED_Command(0x8F);
    OLED_Command(SSD1306_SET_PRECHARGE_PERIOD);
    OLED_Command(0xF1);
    OLED_Command(SSD1306_SET_VCOM_DESELECT);
    OLED_Command(0x40);
    OLED_Command(SSD1306_DISPLAY_ALL_ON_RESUME);
    OLED_Command(SSD1306_NORMAL_DISPLAY);
    OLED_Command(SSD1306_DEACTIVATE_SCROLL);
    OLED_Command(SSD1306_DISPLAY_ON);
}

// Function to write a string to OLED, passed string
void OLED_WriteString(char *characters)
{
  while (*characters) OLED_WriteCharacter(*characters++);
}

// Function to write a character, passed character
void OLED_WriteCharacter(char character)
{
  for (int i=0; i<5; i++) OLED_Data((ASCII[character - 0x20][i]));
  OLED_Data(0x00);
}

void OLED_SetContrast(uint8_t contrast)
{
  OLED_Command(SSD1306_SET_CONTRAST_CONTROL);
  OLED_Command(contrast);
}

// Function to clear OLED by writing to it.
void OLED_Clear(void)
{
    OLED_SelectPage(0);
    
    // OLED 128* 32 pixels = total pixels -> (4096 / 1 byte) = 512 passes.
    // SSD1306_CLEAR_SIZE  = 512 for 128*32 or 1024 for 128*64
    for (int i = 0; i < SSD1306_CLEAR_SIZE; i++) 
    {
      OLED_Data(0x00); // clear OLED screen  
    }
}

void OLED_Fill(void)
{
    OLED_SelectPage(0);
    for (int i = 0; i < SSD1306_CLEAR_SIZE; i++)
    {
        OLED_Data(0xFF); // Fill OLED screen
    }
}

//function to clear OLED  line passed page number
void OLED_ClearLine(uint8_t page_num)
{
    OLED_SelectPage(page_num);
  
    // Clear line of 128 pixels of current page
    for (int i = 0; i < 128 ; i++) 
    {
      OLED_Data(0x00); // clear OLED screen  
    }
}

// Function to select [page] i.e. row or line number
// 128 * 32 has page 0-3
// 128 * 64 has page 0-7
// Passed page num / byte
// page 0   8 
// page 1   16
// page 2   24
// page 3   32
// page 4   40
// page 5   48
// page 6   56
// page 7   64

void OLED_SelectPage(uint8_t page_num)
{
    uint8_t result = 0xB0 | page_num; // Mask or with zero lets everything thru
    OLED_Command(result);
    OLED_Command(SSD1306_SET_LOWER_COLUMN);
    OLED_Command(SSD1306_SET_HIGHER_COLUMN); 
}