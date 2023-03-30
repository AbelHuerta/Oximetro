
#include "I2C.h"

//SSPSTAT 
//SSPCON1 
//SSPCON2 
//SSPBUF  
//SSPSR   = NO DIRECTAMENTE ACCESIBLE(?)
//SSPADD  = 119 (100kHz)


void Master_Mode(void){
    //SE DEBE CONFIGURAR COMO ENTRADA Y SALIDA RB0 Y RB1/SDA Y SCL
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    //CONFIGURACION DE VELOCIDAD ESTANDAR(100kHz y 1MHz)
    SSPSTATbits.SMP = 1;
    //HABILITA LOS PUERTOS SDA Y SCL; RB0 Y RB1
    SSPCON1bits.SSPEN = 1;
    //SELECCION DEL MODO MAESTRO
    SSPCON1bits.SSPM3 = 1;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM0 = 0;

    
    /*
     * BitRate = clock = FOSC/(4 * (SSPADD + 1))
     * (SSPADD + 1) = (FOSC/4)/BitRate
     * SSPADD = ((FOSC/4)/BitRate) - 1
     * SE TIENE UN RELOJ DE 20MHz Y EN CONFIGURACION PLL ES 48MHz
     * Y SE DESEA UNA FRECUENCIA DE RELOJ I2C DE 100 kHz
     * SSPADD = ((48Mhz/4)/100kHz) - 1 = 119
     */
    SSPADD = (uint8_t)Baud_Rate();
    SSPCON2 = 0x00;
}

void I2C_Start(void){
    
    //Inicie la condición de inicio en los pines SDA y SCL
    //Se borra automaticamente por hardware
    SSPCON2bits.SEN = 1;
    //Condicion de espera
    while(SSPCON2bits.SEN == 1);
}

void I2C_ADDRESS_SLAVE(uint8_t address, uint8_t modo){
    uint8_t data = 0;

    data = ((address & 0xFE)) | (modo & 0x01) ;
    SSPBUF = data;
    //El estado de ACK se escribe en el bit ACKDT en el flanco descendente del noveno reloj.
    //Si el maestro recibe un reconocimiento, el bit de estado de reconocimiento, ACKSTAT, se borra
    //El dispositivo maestro enviará un bit ACK al dispositivo esclavo después de recibir los 7bits + 1bit.
    SSPCON2bits.ACKDT = 0;
    //Inicie la secuencia de reconocimiento en los pines SDA y SCL(habilitar). Se borra automáticamente por hardware
    SSPCON2bits.ACKEN = 1;
    //Se debe generar una interrupcion por cada byte de transferencia de datos
    PIR1bits.SSPIF = 0;
    while(PIR1bits.SSPIF == 0);
      
}

void I2C_Write_Data(uint8_t data){
    
    SSPBUF = data;
    //El dispositivo maestro enviará un bit ACK al dispositivo esclavo después de recibir un byte de datos.(ACK)
    SSPCON2bits.ACKDT = 0;
    //Inicie la secuencia de reconocimiento en los pines SDA y SCL(habilitar). Se borra automáticamente por hardware
    SSPCON2bits.ACKEN = 1;
    //El bit indicador, SSPIF (PIR1<3>), debe borrarse en software nuevamente.
    PIR1bits.SSPIF = 0;
    while(PIR1bits.SSPIF == 0);
    
}

void I2C_Stop(void){
    
    //Inicie la condicion de parada de los pines SDA y SCL
    //Se borra automaticamente por hardware
    SSPCON2bits.PEN = 1;
    //Condicion de espera
    while(SSPCON2bits.PEN == 1);
}