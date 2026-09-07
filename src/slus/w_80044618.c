#include "common.h"

/* Checks the just-polled controller id (VSync(1)'s return value, high byte)
 * against the last cached id for this pad slot (arg0==2 selects a 9-bit id
 * mask 0x1FF; any other arg0 uses an 8-bit mask 0xFF). If it matches the
 * cache, returns 2 immediately. Otherwise updates the cache and returns
 * func_800542BC()'s result (a queue/processor kick). */
extern s32 VSync(s32 mode);
extern s32 func_800542BC(void);

/* D_80080AFC / D_80080AFC+2: two contiguous u16 globals; only the second
 * (offset +2) is touched here (a "last reported controller id" cache). */
extern u16 D_80080AFC[2];

s32 func_80044618(s32 arg0) {
    u16 field;
    u16 var_v0;
    s32 ret;
    u32 v1;
    u32 v1_2;

    ret = VSync(1);
    field = D_80080AFC[1];
    v1 = (u32) ret >> 8;
    if (arg0 == 2) {
        if ((v1 & 0x1FF) == field) {
            return 2;
        }
        goto block_4;
    }
    if ((v1 & 0xFF) != field) {
block_4:
        v1_2 = (u32) ret >> 8;
        if (arg0 == 2) {
            var_v0 = v1_2 & 0x1FF;
        } else {
            var_v0 = v1_2 & 0xFF;
        }
        D_80080AFC[1] = var_v0;
        return func_800542BC();
    }
    return 2;
}
