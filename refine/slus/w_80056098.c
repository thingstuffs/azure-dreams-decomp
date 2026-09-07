#include "common.h"

#include "common.h"

/* D_80085458 element (stride 0x78). Envelope channel A. */
typedef struct {
    /* 0x00 */ u8 pad00[0x25];
    /* 0x25 */ s8 f25;
    /* 0x26 */ u8 f26;
    /* 0x27 */ s8 f27;
    /* 0x28 */ u8 f28;
    /* 0x29 */ u8 pad29[3];
    /* 0x2C */ s32 f2c;
    /* 0x30 */ s32 f30;
    /* 0x34 */ u8 f34;
    /* 0x35 */ u8 f35;
    /* 0x36 */ u8 f36;
    /* 0x37 */ u8 pad37;
    /* 0x38 */ s32 f38;
    /* 0x3C */ s32 f3c;
} S_80085458;

/* Advance the envelope delay, level ramp, and triangular modulation output. */
void func_80056098(S_80085458 *envelope) {
    s32 target_level;
    register s32 level ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 scaled_wave;
    s32 phase;
    register s32 doubled_phase ASM_REG("$5");   /* MATCH pin: slus-diff */
    s32 wave;
    u8 delay_ticks;
    u8 ramp_ticks;
    u8 *phase_unsigned;
    s8 *phase_signed;

    target_level = envelope->f30;
    if (target_level != 0) {
        delay_ticks = envelope->f26;
        if (delay_ticks != envelope->f34) {
            envelope->f26 = delay_ticks + 1;
            return;
        }
        ramp_ticks = envelope->f28;
        if (ramp_ticks >= envelope->f35) {
            envelope->f2c = target_level;
        } else {
            if (ramp_ticks != 0) {
                /* split so f2c loads into $v0 first, then f38 into $v1 */
                level = envelope->f2c;
                level = level + envelope->f38;
            } else {
                level = envelope->f38;
            }
            envelope->f2c = level;
            envelope->f28 = envelope->f28 + 1;
        }
        /* Dual-typed pointers defeat store-load CSE → sb then lb.
           f25=0 early is scheduled into bgez delay under -fno-schedule-insns
           with schedule-insns2 still active. */
        phase_unsigned = (u8 *)&envelope->f27;
        phase_signed = &envelope->f27;
        *phase_unsigned = *phase_unsigned + envelope->f36;
        envelope->f25 = 0;
        phase = *phase_signed;
        if (phase < 0) {
            phase = -phase;
            doubled_phase = phase << 1;
            wave = doubled_phase;
            if ((phase << 25) < 0) {
                wave = -doubled_phase;
            }
            scaled_wave = envelope->f2c * (s8)wave;
            if (scaled_wave > 0) {
                scaled_wave = -scaled_wave;
            }
        } else {
            doubled_phase = phase << 1;
            wave = doubled_phase;
            if ((phase << 25) < 0) {
                wave = -doubled_phase;
            }
            scaled_wave = envelope->f2c * (s8)wave;
            if (scaled_wave < 0) {
                scaled_wave = -scaled_wave;
            }
        }
        if (scaled_wave != 0) {
            if (scaled_wave < 0) {
                scaled_wave += 0x3FF;
            }
            envelope->f3c = scaled_wave >> 10;
            return;
        }
        envelope->f3c = 0;
    }
}
