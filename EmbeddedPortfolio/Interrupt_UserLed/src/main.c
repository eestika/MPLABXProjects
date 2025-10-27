/*******************************************************************************
  Main Source File

  Company: Perez Dynamics
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Led Interrupt External button

  Description:
    Questo programma utilizza un interruttore esterno associato all?interrupt INT1
    per il toggle del LED su RE3, con debounce software.
*******************************************************************************/

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"   // SYS function prototypes
#include "input.h" 

// LED su RE3 (sinking)
static inline void LED_RE3_Init(void){
    TRISEbits.TRISE3 = 0;
    LATESET = (1u << 3);     // spento (sinking)
}

// Callback eseguita dal modulo INPUT
static void OnUserPressed(void)
{
    LATEINV = (1u << 3);     // toggle LED
}

int main(void)
{
    SYS_Initialize(NULL);
    LED_RE3_Init();

    // Inizializza il modulo input con debounce 20 ms
    INPUT_Init(20);
    INPUT_RegisterCallback(OnUserPressed);

    __builtin_enable_interrupts();

    while (1)
    {
        Nop();   // tutto gestito via interrupt
    }
}

/*******************************************************************************
 End of File
*/


