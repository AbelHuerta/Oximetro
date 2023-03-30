
#include "TIMER1.h"

void __interrupt(high_priority) HighISR(void){
    //Verificaci�n de la interrupci�n deseada
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
       //1. C�digo de atenci�n de la interrupci�n
       LATCbits.LATC1 = ~LATCbits.LATC1;
       //2. Restablecimiento de las condiciones para que se pueda producir la interrupci�n
       TMR1H = 0x6;
       TMR1L = 0xF9; 
       //3. Restablecimiento de la bandera
       PIR1bits.TMR1IF = 0;
       //4. contador para la temporizacion de 10 segundos aumenta
       cont1++;
       
       
     }
}

void Timer1_enable(void){
    //TIMER 0 APAGADO
    T1CONbits.TMR1ON = 0;
    //TIMER DE 16BITS
    T1CONbits.RD16 = 1;
    //SALIDA DE RELOJ DEL CICLO DE SISTEMA (FOSC/4)
    T1CONbits.TMR1CS = 0;
    
    //SELECCION DEL PREESCALADOR 1:8
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;
    
    //
    T1CONbits.T1OSCEN = 0;
    //TMR0
    TMR1H = 0x6;
    TMR1L = 0xF9;  
    //TIMER 0 ENCENDIDO
    T1CONbits.TMR1ON = 1;
    
}

/*void Interrupt_global(void){
    //Deshabilitar los niveles de prioridad en las interrupciones
    RCONbits.IPEN = 0;
    //Activaci�n de interrupci�n global
    INTCONbits.GIE_GIEH = 1; 
    //Habilitaci�n de interrupci�n perif�rica
    INTCONbits.PEIE_GIEL = 1;
}
*/
void Interrupt_TIMER1(void){
    //Habilita la interrupci�n de desbordamiento TMR0
    PIE1bits.TMR1IE = 1;
    //El registro TMR0 no se desbord�
    PIR1bits.TMR1IF = 0;
}