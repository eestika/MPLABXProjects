#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

/** Inizializza il modulo INPUT su INT1 (RE8) con debounce software. */
void INPUT_Init(uint32_t debounce_ms);

/** Registra la callback utente eseguita alla pressione del pulsante. */
void INPUT_RegisterCallback(void (*cb)(void));

#endif // INPUT_H
