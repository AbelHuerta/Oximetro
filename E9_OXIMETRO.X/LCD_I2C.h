/* 
 * File:   LCD_I2C.h
 * Author: abelh
 *
 * Created on 28 de marzo de 2023, 11:17 PM
 */

#ifndef LCD_I2C_H
#define	LCD_I2C_H

#include <stdint.h>
#include <xc.h>
#include "Configuracion.h"
#include "I2C.h"
#include <pic18f4550.h>

//DIRECCION DEL PCF8574
#define DIREC_PCF8574   0x40//direccion
#define DIREC_A0_A2     0x07//H-H-H

//PINES P0 - P7
#define P0 0x01
#define P1 0x02
#define P2 0x04
#define P3 0x08
#define P4 0x10
#define P5 0x20
#define P6 0x40
#define P7 0x80

//PINES DE LA LCD
#define PIN0_RS         P0
#define PIN1_RW         P1
#define PIN2_E          P2
#define BACKLIGHT       P3
#define D4              P4
#define D5              P5
#define D6              P6
#define D7              P7

void PCF8574_Write(uint8_t byte);
void LCD_I2C_nibble(char ctrl,char cmd);
void LCD_I2C_Databus( char ctrl,char cmd);
void LCD_I2C_Init(void);
void LCD_I2C_WriteText(uint8_t row, uint8_t col, char* string);

#endif	/* LCD_I2C_H */

