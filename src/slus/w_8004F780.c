#include "common.h"

/* Interpolates a byte value from a lookup table (D_80071790, keyed via two
 * column indices into a 3-byte-stride row array D_80071784) and writes the
 * LERP result into a 3-byte target buffer (RGB-style triple, all channels
 * set to the same interpolated value), once per entry in a0->entries[0..count). */
typedef struct S_8004F780_Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *buf;
} S_8004F780_Obj;

typedef struct S_8004F780_Entry {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ S_8004F780_Obj *obj;
} S_8004F780_Entry;

typedef struct S_8004F780 {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ S_8004F780_Entry *entries[8];
    /* 0x24 */ s32 count;
    /* 0x28 */ s32 divisor;
    /* 0x2C */ s32 multiplier;
    /* 0x30 */ s32 idxB;
    /* 0x34 */ s32 idxA;
} S_8004F780;

extern u8 D_80071784[];
extern u8 D_80071790[];

void func_8004F780(S_8004F780 *a0)
{
    s32 i;
    u8 *row;
    s32 valA;
    s32 valB;
    s32 quot;
    S_8004F780_Entry *entry;
    S_8004F780_Obj *obj;

    for (i = 0; i < a0->count; i++) {
        entry = a0->entries[i];
        row = D_80071784 + i * 3;
        valA = D_80071790[row[a0->idxA] * 4];
        valB = D_80071790[row[a0->idxB] * 4];
        quot = (valB - valA) * a0->multiplier / a0->divisor;

        obj = entry->obj;
        obj->buf[0] = valA + quot;
        obj->buf[1] = obj->buf[0];
        obj->buf[2] = obj->buf[0];
    }
}
