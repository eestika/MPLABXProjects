#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Inizializza il tasto USER
void INPUT_Initialize(void);

// Verifica se il tasto USER è stato premuto
bool INPUT_UserPressed(void);

#endif // INPUT_H