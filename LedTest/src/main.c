/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Perez Dinamycs

  @File Name
    main.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
#include <xc.h>
#include "config_bits.h"

#define LED_TRIS TRISE   // Registro di direzione (0 = output)
#define LED_LATCH LATE   // Registro per accendere/spegnere i LED

int main(void) {
    // Configura i pin RE0-RE3 come uscite
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;

    

    // Accende i LED (modalità sinking ? 0 = acceso)
    LED_LATCH = 0x00;  

    while (1) {
        // Inverti lo stato di tutti i LED
        LED_LATCH ^= 0x0F; // Cambia stato ai 4 bit meno significativi (RE0-RE3)
        for (volatile int i = 0; i < 3000000; i++); // Ritardo per osservare il lampeggio
    }
}



/* *****************************************************************************
 End of File
 */
