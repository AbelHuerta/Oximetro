/* 
 * File:   I2C.h
 * Author: abelh
 *
 * Created on 28 de marzo de 2023, 11:17 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include <pic18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Configuracion.h"

/*
 * MACROS
 */
#define I2C_WRITE 0x00
#define I2C_READ  0x01

#define Bit_Rate  100000UL //100kHz
#define Baud_Rate() (((FCY/4)/Bit_Rate) - 1)

/*
 *FUNCIONES
 */
void Master_Mode(void);
void I2C_Start(void);
void I2C_ADDRESS_SLAVE(uint8_t address, uint8_t modo);
void I2C_Write_Data(uint8_t data);
void I2C_Stop(void);

#endif	/* I2C_H */

