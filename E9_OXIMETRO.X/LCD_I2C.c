
#include "LCD_I2C.h"

void PCF8574_Write(uint8_t byte){
    
    I2C_Start();
    I2C_ADDRESS_SLAVE((DIREC_PCF8574 | (DIREC_A0_A2<<1)),0x00); //DIRECCION DEL INTEGRADO PCF8574
    I2C_Write_Data((byte | BACKLIGHT)); //DATA
    I2C_Stop();
}

void LCD_I2C_Databus(char ctrl,char cmd){
    uint8_t data;
    
    if((cmd & 1) == 1){
        data = data | D4;
    }else{
        data = data &~ D4;
    }
    
    if((cmd & 2) == 2){
        data = data | D5;
    }else{
        data = data &~ D5;
    }
    
    if((cmd & 4) == 4){
        data = data | D6;
    }else{
        data = data &~ D6;
    }
    
    if((cmd & 8) == 8){
        data = data | D7;
    }else{
        data = data &~ D7;
    }
    
    __delay_us(60);
    
    //Registro de datos o caracter
    if(ctrl == 1){
        data = data | PIN0_RS;
    }else{ //control/instrucción
        data = data &~ PIN0_RS;
    }
    
    PCF8574_Write(data | PIN2_E);
    __delay_us(2);
    PCF8574_Write(data &~ PIN2_E);
}

void LCD_I2C_nibble(char ctrl,char cmd){
    
    LCD_I2C_Databus(ctrl,cmd>>4);
    LCD_I2C_Databus(ctrl,cmd&0x0F);
    
}


void LCD_I2C_Init(void){
    
    //Master_Mode();
    I2C_Start();
    I2C_ADDRESS_SLAVE((DIREC_PCF8574 | (DIREC_A0_A2<<1)),0x00);
    I2C_Write_Data(0x00);
    I2C_Stop();
    __delay_ms(15);
    //CONFIGURACION LCD DE 4 BIT
    /*PCF8574_Write(0x03);
    
    PCF8574_Write(0x03);
    
    PCF8574_Write(0x03);
    
    PCF8574_Write(0x02);
    PCF8574_Write(0x02);
    PCF8574_Write(0x08);
    PCF8574_Write(0x00);
    PCF8574_Write(0x08);
    PCF8574_Write(0x00);
    PCF8574_Write(0x01);
    PCF8574_Write(0x00);
    PCF8574_Write(0x0C); //DISTINTO AL DATASHEET
    */
    LCD_I2C_Databus(0,0x03);
    __delay_ms(5);
 
    LCD_I2C_Databus(0,0x03);
    __delay_ms(5);
    
    LCD_I2C_Databus(0,0x03);
    __delay_ms(5);
    
    LCD_I2C_Databus(0,0x02);
    __delay_ms(5);
    LCD_I2C_nibble(0,0x028);
    __delay_ms(5);
    LCD_I2C_nibble(0,0x08);
    __delay_ms(5);
    LCD_I2C_nibble(0,0x01);
    __delay_ms(5);
    LCD_I2C_nibble(0,0x06);
    __delay_ms(5);
    LCD_I2C_nibble(0,0x0F);//LCD_I2C_Databus(0x0C); //DISTINTO AL DATASHEET
    __delay_ms(5);
}

void LCD_I2C_WriteText(uint8_t row, uint8_t col, char* string){
    //row -> 0,1,2,3        
    //col -> 0,1,..,19
    switch (row) {
        case 0: col = col + 0x80;
                LCD_I2C_nibble(0x00,col);
                break; // fila 0 su columna "0-19"
                
        case 1: col = col + 0xC0;
                LCD_I2C_nibble(0x00,col);
                break; // fila 1 su columna "0-19"
                
        case 2: col = col + 0x94;
                LCD_I2C_nibble(0x00,col);
                break; // fila 2 su columna "0-19"
                
        case 3: col = col + 0xD4;
                LCD_I2C_nibble(0x00,col);
                break; // fila 3 su columna "0-19"
                
        default:col = col + 0x80;
                LCD_I2C_nibble(0x00,col);
                break; // fila 0 
               
    }
    
    
    //while(*string != '\0')
    while (*string)
        LCD_I2C_nibble(0x01,*string++);
}