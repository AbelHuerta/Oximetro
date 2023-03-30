/* 
 * File:   ADC.h
 * Author: abelh
 *
 * Created on 28 de marzo de 2023, 11:18 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdlib.h>

/*
 *MACROS
 */
#define AN0 0
#define AN1 1
#define AN2 2
#define AN3 3

void ADC_Conversion(void);
uint16_t ADC_Read(uint8_t CHx);

#endif	/* ADC_H */

