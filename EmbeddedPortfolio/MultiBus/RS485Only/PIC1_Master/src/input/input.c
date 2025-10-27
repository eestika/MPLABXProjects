#include "input.h"
#include "definitions.h"

void INPUT_Initialize(void)
{
    // Configura RE6 come input
    TRISESET = (1 << 6);
}

bool INPUT_UserPressed(void)
{
    static bool previousState = true;
    bool currentState = (PORTE & (1 << 6)) != 0;

    if (previousState == true && currentState == false)
    {
        previousState = currentState;
        return true;
    }

    previousState = currentState;
    return false;
}
