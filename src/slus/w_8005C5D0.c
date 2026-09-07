#include "common.h"

/* 12-byte struct; entries in D_80086C00[8] */
typedef struct {
    s16 field_0;
    s16 field_2;
    s8 pad4[4];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 D_80086C00[8];
extern s32 func_80059D60(void);

/* Checks D_80086C00[a0].field_2; if it equals 1, calls func_80059D60(); if
   the result is 3, stores it back into field_2. Returns D_80086C00[a0].field_2. */
s16 func_8005C5D0(s16 a0)
{
    S_80086C00 *base = D_80086C00;
    S_80086C00 *p = &base[a0];

    if (p->field_2 == 1) {
        s32 v1 = func_80059D60();
        if (v1 == 3) {
            p->field_2 = (s16)v1;
        }
    }
    return D_80086C00[a0].field_2;
}
