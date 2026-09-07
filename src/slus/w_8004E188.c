#include "common.h"

/* Sets record fields 0x8-0xB from parameter a1, selected via D_800714B0[a1&0xFF] flags */
/* Flags table indexed by a full byte value (0-255); bit 0x10/0x20 => "range A",
   bit 0x40 => "range B", bit 0x80 => "range C" encoding selector. */
extern u8 D_800714B0[];
/* Pre-packed word table, one s32 per byte-index, used for the "range C" case. */
extern s32 D_80071410[];

/* Struct describing the caller-supplied record; fields 0x8-0xB form either four
   individually-set byte fields, or (in the word case) a single packed s32. */
typedef struct {
    u8 pad0[8];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} S_8004E188;

void *func_8004E188(void *a0, s32 a1)
{
    S_8004E188 *s = (S_8004E188 *)a0;
    u8 idx = (u8)a1;
    u8 *p = D_800714B0 + idx;
    u8 flags = *p;
    s32 v0;

    if (flags & 0x30) {
        v0 = (a1 & 0xF) << 3;
        s->f8 = v0;
        v0 = (u32)(a1 & 0x70) >> 1;
        s->f9 = v0;
        s->fA = 8;
        s->fB = 8;
    } else if (flags & 0x40) {
        v0 = (a1 & 0xF) << 3;
        s->f8 = v0;
        v0 = (a1 & 0xF0) - 0x60;
        s->f9 = v0;
        s->fA = 8;
        s->fB = 8;
    } else if (flags & 0x80) {
        *(s32 *)&s->f8 = D_80071410[idx];
    }

    return s;
}
