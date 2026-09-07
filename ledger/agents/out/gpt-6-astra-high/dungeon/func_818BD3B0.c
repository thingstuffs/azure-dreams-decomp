#include "common.h"
#include "m2c_compat.h"

typedef struct S_818BD3B0_0_pre {
    u16 unk_00;
} S_818BD3B0_0_pre;   /* the 0x2 bytes before arg0 in func_818BD3B0, addressed as arg0[-1] */

typedef struct S_818BD3B0_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
} S_818BD3B0_0;   /* arg0 in func_818BD3B0 */

typedef struct S_818BD3B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD3B0_1;   /* temp_v1 in func_818BD3B0 */

typedef struct S_818BD3B0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD3B0_2;   /* arg1 in func_818BD3B0 */

typedef struct S_818BD3B0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD3B0_3;   /* arg2 in func_818BD3B0 */


extern void func_80024D10(void) __attribute__((noreturn));
s32 func_8003DB94();
s32 func_800478B8();
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[3];
extern M2C_UNK D_800DEC70[3];

/* Advance orbital motion, expire it at its duration, and update the object. */
void func_818BD3B0(void *motion, S_818BD3B0_2 *position, S_818BD3B0_3 *object) {
    s16 angle;
    s32 radius_product;
    s32 height_offset;
    u16 tick;
    S_818BD3B0_1 *owner;

    owner = ((S_818BD3B0_0 *)motion)->unk_00;
    owner->unk_14 = (u16) (owner->unk_14 + 1);
    tick = ((S_818BD3B0_0 *)motion)->unk_04 + 1;
    ((S_818BD3B0_0 *)motion)->unk_04 = tick;
    if (((S_818BD3B0_0 *)motion)->unk_06 < (s16) tick) {
        ((S_818BD3B0_0_pre *)motion)[-1].unk_00 = (u16) (((S_818BD3B0_0_pre *)motion)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_80024D10();
        return;
    }
    height_offset = (s32) ((func_80064584((s16) tick << 7) >> 4) * ((S_818BD3B0_0 *)motion)->unk_0A) >> 8;
    ((S_818BD3B0_0 *)motion)->unk_08 = (s16) height_offset;
    position->unk_08 = (s32) (position->unk_14 - (height_offset << 0x10));
    radius_product = (func_800644B8((s16) ((S_818BD3B0_0 *)motion)->unk_04 << 7) >> 4) * ((S_818BD3B0_0 *)motion)->unk_0A;
    angle = ((S_818BD3B0_0 *)motion)->unk_0C + 0x80;
    ((S_818BD3B0_0 *)motion)->unk_0C = (u16) angle;
    ((S_818BD3B0_0 *)motion)->unk_08 = (s16) (radius_product >> 8);
    position->unk_00 = (s32) (position->unk_0C + (((func_80064584(angle) >> 4) * ((S_818BD3B0_0 *)motion)->unk_08) << 8));
    position->unk_04 = (s32) (position->unk_10 + (((func_800644B8((s16) ((S_818BD3B0_0 *)motion)->unk_0C) >> 4) * ((S_818BD3B0_0 *)motion)->unk_08) << 8));
    func_800478B8(object);
    if (object->unk_14 & 0x6000) {
        func_8003DB94(object, &D_800DEC70, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and s0/s2/s1 lifetime shape.
   The zero-argument func_80024D10 edge is noreturn, enabling LEAD 18 to replace
   jal-plus-epilogue with retail's tail j while retaining the global store slot. */
