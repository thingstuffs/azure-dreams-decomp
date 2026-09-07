#include "common.h"

s32 func_80069EF8(void);
s32 func_80024184(void) __attribute__((noreturn));

/* Samples a random value below the limit, yielding zero for nonpositive limits. */
s32 func_8192286C(s32 limit) {
    register s32 result ASM_REG("$2");   /* MATCH pin: retail delay-slot contents depend on it */
    s32 sample;

    if (limit < 0) {
        limit = 0;
    }

    sample = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                sample = (func_80069EF8() & 0xC) >> 2;
            } while (sample >= limit);
            result = sample;
            ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024184();
        }
        if (limit < 0x11) {
            do {
                sample = (func_80069EF8() & 0xF0) >> 4;
            } while (sample >= limit);
            result = sample;
            ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024184();
        }
        if (limit < 0x41) {
            do {
                sample = (func_80069EF8() & 0xFC) >> 2;
            } while (sample >= limit);
            result = sample;
            ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024184();
        }
        if (limit < 0x101) {
            do {
                sample = (func_80069EF8() & 0xFF0) >> 4;
            } while (sample >= limit);
            result = sample;
            ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024184();
        }
        if (limit < 0x1001) {
            do {
                sample = func_80069EF8() & 0xFFF;
            } while (sample >= limit);
            result = sample;
            ASM_KEEP(result);   /* MATCH pin: retail delay-slot contents depend on it */
            func_80024184();
        }
        do {
            sample = func_80069EF8() & 0xFFFF;
        } while (sample >= limit);
    }
    return sample;
}
