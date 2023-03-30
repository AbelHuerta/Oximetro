
#include "TIMER0.h"

#pragma interruptlow LowISR
void __interrupt(low_priority) LowISR(void){
    //Verificación de la interrupción deseada
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
       //1. Código de atención de la interrupción
       LATCbits.LATC0 = ~LATCbits.LATC0;
       //2. Restablecimiento de las condiciones para que se pueda producir la interrupción
       TMR0H = 0x48;
       TMR0L = 0xE4; 
       //3. Restablecimiento de la bandera
       INTCONbits.TMR0IF = 0;
       //4. contador para la temporizacion de 10 segundos aumenta
       cont++;
       
     }
    
    
}

void Timer0_enable(void){
    //TIMER 0 APAGADO
    T0CONbits.TMR0ON = 0;
    //TIMER DE 16BITS
    T0CONbits.T08BIT = 0;
    //SALIDA DE RELOJ DEL CICLO DE SISTEMA (FOSC/4)
    T0CONbits.T0CS = 0;
    //SELECCION DE FLANCO DE SUBIDA
    T0CONbits.T0SE = 0;
    //ACTIVA EL PREESCALADOR
    T0CONbits.PSA = 0;
    //SELECCION DEL PREESCALADOR 1:256
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;
    //TMR0
    TMR0H = 0x48;
    TMR0L = 0xE4;
    //TIMER 0 ENCENDIDO
    T0CONbits.TMR0ON = 1;
    
}

void Interrupt_global(void){
    //Habilitar prioridades de interrupción
    RCONbits.IPEN = 1;
    INTCON2bits.TMR0IP = 0;     //Low priority
    IPR1bits.TMR1IP = 1;        //High priority
    /*INTCONbits.GIEH = 1; // Habilitar las interrupciones de alta prioridad
    INTCONbits.GIEL = 1; // Habilitar las interrupciones de baja prioridad*/
    //Activación de interrupción global
    INTCONbits.GIE_GIEH = 1; 
    //Habilitación de interrupción periférica
    INTCONbits.PEIE_GIEL = 1;
}

void Interrupt_TIMER0(void){
    //Habilita la interrupción de desbordamiento TMR0
    INTCONbits.TMR0IE = 1;
    //El registro TMR0 no se desbordó
    INTCONbits.TMR0IF = 0;
}