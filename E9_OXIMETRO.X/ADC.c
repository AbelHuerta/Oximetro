
#include "ADC.h"
#include "Configuracion.h"

//FCY = 48MHz -> T = 20.83ns
//TAD minimo es 0.7us
//TAD = 64*T = 64*20.83ns = 1.3us
//TACQ minimo es 6.4us
//TACQ = 6*TAD = 6*1.3us = 7.8us

void ADC_Conversion(void){
    //LA CONVERSION NO ESTA EN PROCESO
    ADCON0bits.GO_DONE = 0;
    //Se habilita el ADC
    ADCON0bits.ADON = 1;
    
    //VOLTAJE DE REFERENCIA
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;
    
    //CANAL ANALOGICO(AN0)
    ADCON1bits.PCFG3 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 0;
    
    //JUSTIFICADO A LA DERECHA
    ADCON2bits.ADFM = 1;
    
    //TIEMPO DE ADQUISICION
    ADCON2bits.ACQT2 = 0;
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT0 = 1;
    
    //RELOJ DE CONVERSION
    ADCON2bits.ADCS2 = 1;
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS0 = 0;
    
}

uint16_t ADC_Read(uint8_t CHx){
    
    ADCON0 = (ADCON0 & 0x03) | ((CHx<<2) & 0x3C);
    /*ADCON0bits.CHS3 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;*/
    //Inicia la conversion
    ADCON0bits.GO_DONE = 1;
    //Esperar hasta que la conversion termine
    while(ADCON0bits.GO_DONE)continue ;
    
    __delay_ms(2);
    
    return ((ADRESH<<8)+ADRESL);
}