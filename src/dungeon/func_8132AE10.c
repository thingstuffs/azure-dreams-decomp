#include "common.h"

typedef struct S_80172610_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x68];
    union { s16 s; u16 u; } unk_94;   /* accessed as both */
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x11];
    u8 * unk_AC;
} S_80172610_0;   /* actor in func_80172610 */

typedef struct S_80172610_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80172610_1;   /* owner in func_80172610 */

typedef struct S_80172610_2 {
    u8 pad_00[0x1C];
    union { void * p; u32 i; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
} S_80172610_2;   /* base in func_80172610 */

typedef struct S_80172610_3 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80172610_3;   /* linked in func_80172610 */

typedef struct S_80172610_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0xA];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80172610_4;   /* context in func_80172610 */

typedef struct S_80172610_5 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_80172610_5;   /* state in func_80172610 */

typedef struct S_80172610_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172610_6;   /* output in func_80172610 */

typedef struct S_80172610_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80172610_7;   /* source in func_80172610 */

typedef struct S_80172610_8 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80172610_8;   /* saved_base in func_80172610 */



extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);
extern void func_800A020C(void *, void *);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s8 D_800DCECC[];
extern u8 D_80174C6C[];

void func_80172610(void *arg0, void *arg1, void *arg2)
{
    u8 *actor;
    u8 *output;
    u8 *context;
    u8 *owner;
    u8 *base;
    register u8 *saved_base;
    u8 *linked;
    u8 *source;
    u8 *state;
    s32 first_index;
    s32 work;
    s32 effect_index;
    s32 global_flags;
    s16 compare_index;
    s32 effect;
    s16 old_position;
    s16 new_position;
    u16 new_position_bits;

    actor = arg0;
    output = arg1;
    context = arg2;
    owner = ((S_80172610_0 *)actor)->unk_AC;
    linked = ((S_80172610_1 *)owner)->unk_0C;
    source = ((S_80172610_1 *)owner)->unk_08;
    base = owner + 0x20;
    saved_base = base;

    if (((S_80172610_0 *)actor)->unk_9A != 0) {
        return;
    }

    func_800A020C(((S_80172610_2 *)base)->unk_1C.p, context + 0xC);
    if ((((S_80172610_2 *)base)->unk_1C.i & 0x20) == 0) {
        func_800478B8(context);
    }

    if (((S_80172610_3 *)linked)->unk_2C == D_80174C6C) {
        func_800478B8(context);
        func_800478B8(context);
    }

    old_position = ((S_80172610_0 *)actor)->unk_2A;
    new_position = ((S_80172610_2 *)base)->unk_2A.s;
    new_position_bits = ((S_80172610_2 *)base)->unk_2A.u;
    if (old_position != new_position) {
        (*(u16 *)((u8 *)actor + 0x2A)) = new_position_bits;
        first_index = ((D_80083228 + new_position + 0x100) >> 9) & 7;
        func_80047784(context, (*(u8 *)((u8 *)(((S_80172610_4 *)context)->unk_2C) + first_index)), 0);
    }

    state = D_80083160;
    work = ((((S_80172610_5 *)state)->unk_C8 + ((S_80172610_0 *)actor)->unk_2A + 0x100) >> 9) & 7;
    compare_index = work;
    if (((S_80172610_0 *)actor)->unk_94.s != compare_index) {
        func_80047784(context, (*(u8 *)((u8 *)(((S_80172610_4 *)context)->unk_2C) + compare_index)), 0);
        ((S_80172610_0 *)actor)->unk_94.u = work;
    }

    ((S_80172610_4 *)context)->unk_14 = ((S_80172610_3 *)linked)->unk_14;
    ((S_80172610_6 *)output)->unk_02 = ((S_80172610_7 *)source)->unk_02;
    ((S_80172610_6 *)output)->unk_06 = ((S_80172610_7 *)source)->unk_06;
    ((S_80172610_6 *)output)->unk_0A = ((S_80172610_7 *)source)->unk_0A;

    effect_index = ((((S_80172610_5 *)state)->unk_C8 + ((S_80172610_0 *)actor)->unk_2A + 0x100) >> 9) & 7;
    effect = D_800DCECC[effect_index];
    ((S_80172610_4 *)context)->unk_06 = effect << 2;
    ((S_80172610_4 *)context)->unk_1C = ((S_80172610_3 *)linked)->unk_1C;
    ((S_80172610_4 *)context)->unk_1E = ((S_80172610_3 *)linked)->unk_1E;
    ((S_80172610_4 *)context)->unk_12 = ((S_80172610_3 *)linked)->unk_12;

    if (((S_80172610_1 *)owner)->unk_1E & 0x8000) {
        (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (((S_80172610_8 *)saved_base)->unk_9A == 0x13) {
        ((S_80172610_0 *)actor)->unk_9A++;
        (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
        global_flags = D_800814A0;
        ((S_80172610_0 *)actor)->unk_96 = 0;
        D_800814A0 = global_flags | 0x8000;
    }
}
