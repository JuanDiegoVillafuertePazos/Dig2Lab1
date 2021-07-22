/* 
 * File:   LibreriaTMR0.c
 * Author: Medardo
 *
 * Created on 21 de julio de 2021, 02:56 PM
 */

#include <xc.h>
#include "LibreriaTMR0.h"
#include "LibreriaHex.h"

void TMR0_LIB(void){
        TMR0 = 125;
        INTCONbits.T0IF = 0;
        PORTE++;
}
