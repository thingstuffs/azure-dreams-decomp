#include "common.h"

extern s16 func_80053DA8(s32 arg0);
extern u16 D_80013714;

/* Query the low 16 bits of the input unless flag bit 1 disables the call. */
s32 func_800A56E0(s32 query_value) {
    s32 result;

    if (D_80013714 & 2) {
        result = 0;
    } else {
        result = func_80053DA8(query_value & 0xFFFF);
    }
    return result;
}
