/* 
 * File:   TIMER0.h
 * Author: abelh
 *
 * Created on 28 de marzo de 2023, 11:27 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include <xc.h>
#include <pic18f4550.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/******************************************/
/****    CALCULO DE LA TEMPORIZACION   ****/
/******************************************/
// FCY = 48MHz
// Por el modulo de temporizacion (/4) -> 12MHz
// Por lo tanto:
// T = (4/FCY) * PRE * (65535 - TMR0)
// T = (4/12MHz) * 256 * (65535 - TMR0)
// Para la temporizacion de 1 seg
// 1 =  (4/12MHz) * 256 * (65535 - TMR0)
// LA activacion de la bandera de interrupcion ocurrira cada
// TMR0 = 18660 conteos 
// en Hexadecimal 
// TMR0 = 48E4

/*
 *MACROS
 */
#define Infrarrojo LATBbits.LATB2

/*
 * VARIABLES
 */
int  cont  = 0;

/*
 * FUNCIONES
 */
void Timer0_enable(void);
void Interrupt_global(void);
void Interrupt_TIMER0(void);
void Interrupcion_AltaPrioridad(void);
#endif	/* TIMER0_H */

