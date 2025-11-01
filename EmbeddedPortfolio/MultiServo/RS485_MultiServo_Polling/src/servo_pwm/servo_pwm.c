#include "servo_pwm.h"
#include "definitions.h"   // OCMP1_*, TMR2_*, etc.

static ServoPwmConfig_t s_cfg;
static uint32_t s_ticks_per_us = 0;   // TMR2 ticks per microsecondo
static uint16_t s_min_ticks = 0;
static uint16_t s_max_ticks = 0;

static inline uint16_t clamp_u16(uint16_t v, uint16_t lo, uint16_t hi) {
    return (v < lo) ? lo : (v > hi) ? hi : v;
}

void ServoPWM_Init(const ServoPwmConfig_t *cfg)
{
    /* Copia configurazione (o default) */
    if (cfg) {
        s_cfg = *cfg;
    } else {
        s_cfg.min_us    = 1000;
        s_cfg.mid_us    = 1500;
        s_cfg.max_us    = 2000;
        s_cfg.period_us = 20000;
    }

    /* Calcola ticks/us dal timer selezionato (TMR2 in MCC) */
    uint32_t f_tmr = TMR2_FrequencyGet();         // es. 1_250_000 Hz
    s_ticks_per_us  = (f_tmr + 500000u) / 1000000u; // arrotonda; es. 1_250_000/1_000_000 = 1.25 -> 1

    /* Precalcola range min/max in ticks */
    s_min_ticks = (uint16_t)(s_cfg.min_us * s_ticks_per_us);
    s_max_ticks = (uint16_t)(s_cfg.max_us * s_ticks_per_us);

    /* Abilita moduli: si assume che MCC abbia già configurato:
       - TMR2 (periodo per 20 ms: PR2 = 24999 se f_tmr=1.25 MHz)
       - OCMP1 in Edge-Aligned PWM, timebase TMR2, secondary compare come duty
    */
    TMR2_Start();
    OCMP1_Enable();

    /* Porta su cui è mappato OC1 (es. RD0) come output (facoltativo se MCC l’ha già fatto) */
    TRISDCLR = (1u << 0);

    /* Posiziona al centro */
    ServoPWM_SetPulseUS(s_cfg.mid_us);
}

void ServoPWM_SetPulseUS(uint16_t us)
{
    uint16_t clamped_us = clamp_u16(us, s_cfg.min_us, s_cfg.max_us);
    uint32_t ticks      = (uint32_t)clamped_us * s_ticks_per_us;
    OCMP1_CompareSecondaryValueSet((uint16_t)ticks);
}

void ServoPWM_SetAngleDeg(uint8_t deg)
{
    if (deg > 180u) deg = 180u;

    uint32_t span_us = (uint32_t)(s_cfg.max_us - s_cfg.min_us);
    uint32_t pulse   = (uint32_t)s_cfg.min_us + ((uint32_t)deg * span_us) / 180u;

    ServoPWM_SetPulseUS((uint16_t)pulse);
}
