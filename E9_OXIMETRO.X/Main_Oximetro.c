/* 
 * File:   Main_Oximetro.c
 * Author: abelh
 *
 * Created on 28 de marzo de 2023, 11:12 PM
 */

#include <xc.h>
#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "Configuracion.h"
#include "ADC.h"
#include "I2C.h"
#include "LCD_I2C.h"
#include "TIMER0.h"
#include "TIMER1.h"

/*
 * MACROS
 */
#define S1 PORTAbits.RA1
#define S2 PORTAbits.RA2

/*
 * VARIABLES
 */
uint8_t  bufferTx[20];  //CARACTERES A TRANSMITIR
uint16_t sensor;          //CONVERSION ADC

uint8_t s1_Anterior;
uint8_t s1_Actual;
uint8_t s2_Anterior;
uint8_t s2_Actual;
int C1;
float Referencia, Saturacion;

int main(int argc, char** argv) {
    
    //ENTRADA ANALOGICA
    //TRISAbits.RA0 = 1;
    
    //DEFINIR ENTRADAS
    TRISAbits.RA1 = 1; //ON
    TRISAbits.RA2 = 1; //OFF
    
    //Configurar RC0 COMO SALIDA
    TRISCbits.TRISC0 = 0; 
    //Estado inicial RC0 APAGADO
    LATCbits.LATC0 = 0;
    //Configurar RB2 COMO SALIDA (INFRARROJO)
    TRISBbits.TRISB2 = 0; 
    //Estado inicial RB2 APAGADO (INFRARROJO)
    LATBbits.LATB2 = 0;
    
    
    //Configurar RC1 COMO SALIDA
    TRISCbits.TRISC1 = 0; 
    //Estado inicial RC1 APAGADO
    LATCbits.LATC1 = 0;
    //Configurar RB3 COMO SALIDA (ROJO)
    TRISBbits.TRISB3 = 0; 
    //Estado inicial RB3 APAGADO (ROJO)
    LATBbits.LATB3 = 0;
    
    
    Interrupt_global();
    
    Interrupt_TIMER0();
    Timer0_enable();
    
    Interrupt_TIMER1();
    Timer1_enable();
    
    Master_Mode();
    LCD_I2C_Init();
    ADC_Conversion();
    LCD_I2C_WriteText(0,0,"SP02:");
    for(;;){
        //1.7m segundos
       /*if(cont1>=2){
        Rojo = ~Rojo;
        cont1 = 0;
       }*/
       /*//5 segundos
       if(cont>=5){
        Infrarrojo = ~Infrarrojo;
        cont = 0;
       }*/
        
        
        sensor = ADC_Read(AN0);
        Referencia = sensor * -0.32/1024+0.93;
        Saturacion = -46.208*Referencia+127.89;
        sprintf(bufferTx,"%.02f",Saturacion);
		//LCD_I2C_WriteText(1,0,bufferTx);
		//__delay_ms(100);
                
        if(cont>=5){  //SI se cumplieron 5s del timer0
            Infrarrojo = 1;
            cont = 0;
            LCD_I2C_WriteText(0,6,bufferTx);
            LCD_I2C_WriteText(0,11,"%");
            if(Saturacion > 90.0) {
                LCD_I2C_WriteText(1,0,"SAT. OPTIMA "); // Presentar Texto fijo
            }
            if(Saturacion > 85.0 && Saturacion < 90.0) {
                LCD_I2C_WriteText(1,0,"SAT. MODERADA "); // Presentar Texto fijo
            } 
            if(Saturacion < 85.0) {
                LCD_I2C_WriteText(1,0,"SAT. SEVERA "); // Presentar Texto fijo
            } 
       }
       
        
        s1_Actual = S1;
        if(!s1_Anterior && s1_Actual){ // Si presiona S1
            Rojo=1; //Infrarrojo=0; // Led rojo ON e IF OFF
            C1=1; // Antivar bit de estado C1
            
        }
        s1_Anterior= s1_Actual;
        
        if(cont1>=2){
            if(C1==1){ // Si transcurrio 170us
                Rojo = ~Rojo;
                cont1 = 0;        
            }
        }
        
        s2_Actual=S2; // Leer estado del pulsador
        if(!s2_Anterior && s2_Actual){ // Si se presiona S2
    
            Infrarrojo=0; Rojo=0; // Pulsos nivel bajo
        }
    }
        
    return (EXIT_SUCCESS);
}

