#include "common.h"

/* Fisher-Yates-style shuffle of a byte array of length arg1, using func_800A6D30() as the RNG source. */
extern s32 func_800A6D30(void);

void func_8004A9B0(u8 *arg0, s32 arg1) {
    s32 i;
    s32 j;
    u8 tmp;
    for (i = arg1 - 1; i > 0; i--) {
        j = (func_800A6D30() & 0xFFFF) / ((0x7FFF / (i + 1)) + 1);
        tmp = arg0[i];
        arg0[i] = arg0[j];
        arg0[j] = tmp;
    }
}
