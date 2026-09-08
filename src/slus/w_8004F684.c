#include "common.h"

#include "common.h"

/* Sibling of func_8004F780 (matched @ 2.7.2-cdk): same a0 layout and
 * D_80071784 3-byte-row walk, but writes two interpolated s16 fields
 * (scaled by 30 / 12) into entry->obj->target rather than an RGB triple. */

typedef struct S_8004F684_Target {
    /* 0x00 */ u8 pad[0xA];
    /* 0x0A */ s16 field_A;
    /* 0x0C */ s16 field_C;
} S_8004F684_Target;

typedef struct S_8004F684_Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ S_8004F684_Target *target;
} S_8004F684_Obj;

typedef struct S_8004F684_Entry {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ S_8004F684_Obj *obj;
} S_8004F684_Entry;

typedef struct S_8004F684 {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ S_8004F684_Entry *entries[8];
    /* 0x24 */ s32 count;
    /* 0x28 */ s32 divisor;
    /* 0x2C */ s32 multiplier;
    /* 0x30 */ s32 idxB;
    /* 0x34 */ s32 idxA;
} S_8004F684;

extern u8 D_80071784[];

void func_8004F684(S_8004F684 *a0)
{
    S_8004F684 *self;
    s32 i;
    u8 *row;
    S_8004F684_Entry **slot;
    s32 valA;
    s32 diff;
    s32 m;
    register s32 quot ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 scaled;
    register void *p ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    S_8004F684_Obj *obj;

    self = a0;
    i = 0;
    if (self->count > 0) {
        row = D_80071784;
        slot = (S_8004F684_Entry **)self;
        do {
            valA = row[self->idxA];
            diff = row[self->idxB] - valA;

            m = self->multiplier * 30;
            quot = (diff * m) / self->divisor;
            p = slot[1];
            obj = ((S_8004F684_Entry *)p)->obj;
            p = obj->target;
            scaled = valA * 30;
            quot = quot + 0x200;
            scaled = scaled + quot;
            ((S_8004F684_Target *)p)->field_C = (s16)scaled;

            m = self->multiplier * 12;
            quot = (diff * m) / self->divisor;
            slot++;
            i++;
            p = obj->target;
            scaled = valA * 12;
            quot = quot - 0x40;
            scaled = scaled + quot;
            ((S_8004F684_Target *)p)->field_A = (s16)scaled;

            row += 3;
        } while (i < self->count);
    }
    ASM_KEEP(i);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
}
