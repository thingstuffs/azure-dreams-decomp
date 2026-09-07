#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern u8 D_80080EA8[];
extern u8 D_800CF828[];
extern s32 D_800CF838[];

s32 func_8008B3AC(void) {
    s32 i = 0;
    u8 *bytes = D_800CF828;
    s32 *table = D_800CF838;
    u8 *needle = D_80080EA8;

    do {
        if (table[*(u8 *)((s32)i + (s32)bytes)] == (s32)needle)
            return i;
        i++;
    } while (i < 15);
    return -1;
}
