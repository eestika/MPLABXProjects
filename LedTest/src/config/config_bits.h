/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
#ifndef CONFIG_BITS_H
#define CONFIG_BITS_H

#include <xc.h>

// CONFIGURAZIONE OSCILLATORE
#pragma config FNOSC = PRIPLL   // Usa il Primary Oscillator con PLL
#pragma config POSCMOD = HS     // High-Speed Crystal Mode (dato che abbiamo un quarzo esterno)
#pragma config FPLLMUL = MUL_20 // Moltiplica per 20 il segnale in ingresso
#pragma config FPLLIDIV = DIV_2 // Divide il segnale in ingresso per 2 (da 8 MHz ? 4 MHz)
#pragma config FPLLODIV = DIV_2 // Divide l'uscita per 2 (da 80 MHz ? 40 MHz)

// ALTRI FUSE BITS (opzionali)
#pragma config FPBDIV = DIV_1    // Peripheral Bus Clock = SYSCLK/1 (40 MHz)
#pragma config FWDTEN = OFF      // Disabilita il Watchdog Timer
#pragma config ICESEL = ICS_PGx2 // Debug via PGEC2/PGED2
#pragma config DEBUG = OFF   // Disabilita il debugger hardware


#endif
