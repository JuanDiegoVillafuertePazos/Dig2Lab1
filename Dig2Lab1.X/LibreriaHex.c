/* 
 * File:   LibreriaHex.c
 * Author: Medardo
 *
 * Created on 21 de julio de 2021, 03:18 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <xc.h>
#include "LibreriaHex.h"

char TablaHex(char valorH){
    switch(valorH){
        case 0:
        return 0b00111111;      //cases con su retorno segun cada numero
        break; 
        case 1:
        return 0b01011011;
        break;  
        case 2:
        return 0b01011011;
        break;  
        case 3:
        return 0b01001111;
        break; 
        case 4:
        return 0b01100110;
        break;  
        case 5:
        return 0b01101101;
        break;  
        case 6:
        return 0b01111101;
        case 7:
        return 0b00000111;
        break;  
        case 8:
        return 0b01111111;
        break;  
        case 9:
        return 0b01100111;
        break;
        case 10: //A
        return 0b01110111;
        break;
        case 11: //b
        return 0b01111100;
        break;
        case 12: //C
        return 0b00111001;
        break;
        case 13: //d
        return 0b01011110;
        break;
        case 14: //e
        return 0b01111001;
        break;
        case 15: //F
        return 0b01110001;
        break;
    }
}