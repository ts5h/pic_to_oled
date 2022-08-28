/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1705
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "lib/OLED.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // My settings
    IO_RC3_SetHigh();
    
    OLED_Init();
    OLED_Clear();
    __delay_ms(1000);
    
    // Block
    uint8_t blocks[64] = {};
    for (int i = 0; i < sizeof(blocks); i++) {
        // wait time
        blocks[i] = (uint8_t) rand() % 10000 + 1 * 10;
        
        // color
        blocks[i] += (uint8_t) rand() % 2;
    }
    
    while (1)
    {
        // OLED_SelectPage(0);
        // OLED_WriteString("Hello, World.");
        
        OLED_SelectPage(0);
        for (int i = 0; i < sizeof(blocks); i++) {
            // wait time
            int wait = blocks[i] / 10;
            bool flag = blocks[i] % 2;
            
            if (wait <= 0) {
                flag = !flag;
                blocks[i] = (uint8_t) rand() % 10000 + 1 * 10 + flag;
            } else {
                wait--;
                blocks[i] = (uint8_t) wait * 10 + flag;
            }
            
            for (int j = 0; j < 16; j++) {
                OLED_Data((uint8_t) flag ? 0xFF : 0x00);
            }
        }
    }
}

/**
 End of File
*/