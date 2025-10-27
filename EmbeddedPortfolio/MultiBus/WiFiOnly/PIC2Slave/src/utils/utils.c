#include "utils.h"
#include <definitions.h>  // Per _CP0_GET_COUNT()


// Attende un numero specificato di millisecondi usando il core timer (40MHz)
void DelayMs(uint32_t ms)
{
    uint32_t tStart = _CP0_GET_COUNT();
    uint32_t tWait = (SYS_FREQ / 2000) * ms;
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}


