#include "input.h"
#include "definitions.h"
#include "peripheral/evic/plib_evic.h"

// ===== Core Timer config =====
#ifndef CORE_TIMER_HZ
#define CORE_TIMER_HZ (40000000UL)        // tipico: CPU 80MHz ? CoreTimer 40MHz
#endif
#define MS_TO_CT(ms)  ((CORE_TIMER_HZ/1000U) * (uint32_t)(ms))

// ===== Stato interno =====
static uint32_t          s_debounceTicks = 0;
static volatile uint32_t s_lastCt = 0;
static void (*s_userCb)(void) = 0;

// ===== ISR bridge da EVIC =====
static void INT1_BridgeCallback(EXTERNAL_INT_PIN pin, uintptr_t ctx)
{
    (void)pin; (void)ctx;
    uint32_t now = _CP0_GET_COUNT();

    if ((now - s_lastCt) > s_debounceTicks)
    {
        s_lastCt = now;
        if (s_userCb)
            s_userCb();   // chiama la callback utente
    }
}

void INPUT_Init(uint32_t debounce_ms)
{
    s_debounceTicks = MS_TO_CT(debounce_ms);
    s_lastCt        = 0;
    s_userCb        = 0;

    // INT1 su RE8: fronte di discesa (pull-up esterno + pulsante a GND)
    INTCONSET = _INTCON_INT1EP_MASK;
    IFS0CLR = _IFS0_INT1IF_MASK;

    // Registra la callback bridge e abilita l?interrupt
    EVIC_ExternalInterruptCallbackRegister(EXTERNAL_INT_1, INT1_BridgeCallback, 0);
    EVIC_ExternalInterruptEnable(EXTERNAL_INT_1);
}

void INPUT_RegisterCallback(void (*cb)(void))
{
    s_userCb = cb;
}
