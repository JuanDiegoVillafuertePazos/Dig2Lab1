/*
 * File:   main.c
 * Author: Medardo
 *
 * Created on 20 de julio de 2021, 03:00 PM
 */

#include <xc.h>
#include "LibreriaADC.h"
#include "LibreriaTMR0.h"
#include "LibreriaHex.h"

#pragma config FOSC=INTRC_NOCLKOUT //Oscilador interno sin salida
#pragma config WDTE=OFF           //Reinicio repetitivo del pic
#pragma config PWRTE=OFF           //no espera de 72 ms al iniciar el pic
#pragma config MCLRE=OFF          //El pin MCLR se utiliza como entrada/salida
#pragma config CP=OFF             //Sin protección de código
#pragma config CPD=OFF            //Sin protección de datos
    
#pragma config BOREN=OFF //Sin reinicio cuando el input voltage es inferior a 4V
#pragma config IESO=OFF  //Reinicio sin cambio de reloj de interno a externo
#pragma config FCMEN=OFF //Cambio de reloj externo a interno en caso de fallas
#pragma config LVP=OFF    //Programación en low voltage apagada
    
//CONFIGURATION WORD 2
#pragma config WRT=OFF //Proteccion de autoescritura por el programa desactivada
#pragma config BOR4V=BOR40V //Reinicio abajo de 4V 
#define _XTAL_FREQ 8000000 //frecuencia de 8 MHz

char var;
char num;
char valHex;
char num1;
char num2;
char disp1;
char disp2;
char banderas;

void __interrupt() isr(void){       //apartado de interrupciones
   
    if(RBIF == 1)  {        //interrupciones por boton con antirrebote
        if (PORTBbits.RB0 == 0) {
            var++;
        }
        if (PORTBbits.RB1 == 0) { 
            var--;
        } 
            RBIF = 0;
    }
        ADCON0bits.GO = 1;      //set para el GO que permite hacer la conversion

    if(ADIF==1){
            valHex = ADCnum(num);
            //PORTD = TablaHex(valHex);
            ADIF = 0;
    }
    __delay_us(50);   //delay de 50 us
    
    if (T0IF==1){
        TMR0_LIB();
                
        switch(banderas){
            case 0:
            PORTD = TablaHex(num1);
            banderas++;
            break;
            case 1:
            PORTD = TablaHex(num2);
            banderas = 0;
            break;
        }
   
    }

}
void main(void) {
    //configuraciones 
    //reloj
    OSCCONbits.IRCF = 0b0100;//0100 Frecuencia de reloj 1 MHz
    OSCCONbits.SCS = 1;//reloj interno
    
    //configuracion in out
    ANSEL = 0;
    ANSELH = 32;
    
    TRISA = 0;
    TRISB = 0b00100011;
    TRISC = 0;
    TRISD = 0;
    TRISE = 4;
    
    PORTA = 0; 
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    //ADC
    //configuracion del ADC
    ADCON0 = 0b00110111; 
    ADCON1 = 0b00000000;
    __delay_us(200);   //delay de 50 us
    
    //interrupciones por cambio
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
            
    //configuracion interrupciones por cambio
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    //configuracion tmr1
    /*TMR1L = 0b11011100; 
    TMR1H = 0b00001011;
    T1CONbits.T1CKPS0 = 0; //prescale 1:4
    T1CONbits.T1CKPS1 = 1; 
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;
    PIR1bits.TMR1IF  = 0;*/
    
    //configuracion tmr0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;
    OPTION_REGbits.PS2  = 0;
    OPTION_REGbits.PS1  = 1;
    OPTION_REGbits.PS0  = 1;
    
    //reset tmr0
    TMR0 = 100;
    INTCONbits.T0IF = 0;
    
    //configuracion interrupciones
    INTCONbits.GIE  = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;
    PIE1bits.ADIE   = 1;
    
    while(1){
        PORTC = var;
        num1 = valHex/16;
        num2 = valHex%16;
    }
}
