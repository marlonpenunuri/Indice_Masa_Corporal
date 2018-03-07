
#include <xc.h>
#include "comm.h"
#include "uart.h"
#include "setup_Up.h"


void Op_IMC(void){
    unsigned char dec_pes = 0;
    unsigned int dec_alt_temp = 0;
    unsigned char dec_alt = 0;
    unsigned char dig1_pes = 0;
    unsigned char dig2_alt = 0;
    unsigned int sq_alt = 0; 
    unsigned char dato[6];
    unsigned char num[8];
    unsigned char byte1;
    unsigned char dig1;
    unsigned char dig2;
    unsigned char resultado;
    
    printf_UART ("Calculadora de IMC \n\r");
    printf_UART ("\nIngrese su peso incluyendo una posicion tras el punto: \n\r");
    
    //Obtencion de datos
    for(unsigned char i=0;i<8;i++){ 
        if (i==4){
            printf_UART ("\nIngrese su altura incluyendo dos posiciones tras el punto: \n\r");
        }
        num[i] = scanf_UART();
        putc_UART(num[i]);   
    }
    
    //peso 7.1
    dato[0]=(num[0] & 0x0F);
    dato[1]=(num[1] & 0x0F);
    dato[2]=(num[3] & 0x0F);
    byte1 = dato[0]<<4 | dato[1];
    dig1 = bcd2hex(byte1);
    
    dig1 = dig1 << 1;
    
    if(num[3]>=5){
        dec_pes = 0x01;
    }
    else{
        dec_pes = 0x00;
    }
    
    dig1_pes = dig1 | dec_pes; 

    
    
    //altura 2.6
    dato[3] = (num[4] & 0x0F);
    dato[4] = (num[6] & 0x0F);
    dato[5] = (num[7] & 0x0F);
    byte1 = dato[6]<<4 | dato[7];
    byte1= bcd2hex(byte1);
    
    dig2 = dato[3] << 6;
    
    dec_alt_temp = (byte1*41);
    dec_alt = dec_alt_temp >> 6;
    dec_alt = bcd2hex(dec_alt);
    
    dig2_alt = dig2 | dec_alt;
    
    //alt 4.12
    unsigned int sq_alt2 = (dig2_alt * dig2_alt) >> 8;
    
    //Division
    unsigned int dig1_pes_rec = dig1_pes << 4;
    
    
    resultado = dig1_pes_rec/sq_alt2;
    resultado = hex2bcd(resultado);
    printf_UART ("\nResultado:\n\r");
    ASCII_UART(resultado);
    printf_UART ("\n\n");
}

void main(void){
	config();
    
    while(1){
      Op_IMC();
    }
  
	
}
