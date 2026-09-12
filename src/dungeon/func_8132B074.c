#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172874_0_pre {
    u16 unk_00;
} S_80172874_0_pre;   /* the 0x2 bytes before base in func_80172874, addressed as base[-1] */

typedef struct S_80172874_0 {
    u8 pad_00[0x12];
    union { s16 s; volatile u16 u; u16 p; } unk_12;   /* accessed as both */
    u8 pad_14[0x2];
    union { u16 s; s16 u; } unk_16;   /* accessed as both */
    s16 unk_18;
    u8 pad_1A[0x6];
    void * unk_20;
    void * unk_24;
} S_80172874_0;   /* base in func_80172874 */

typedef struct S_80172874_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172874_1_pre;   /* the 0x14 bytes before parent in func_80172874, addressed as parent[-1] */

typedef struct S_80172874_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80172874_2;   /* arg2 in func_80172874 */

typedef struct S_80172874_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x24];
    void * unk_2C;
} S_80172874_3;   /* owner in func_80172874 */

typedef struct S_80172874_4 {
    u8 pad_00[0x4CE0];
    s32 unk_4CE0;
} S_80172874_4;   /* flag_base in func_80172874 */


typedef struct S_80172874_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172874_6;   /* source in func_80172874 */

typedef struct S_80172874_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80172874_7;   /* global_base in func_80172874 */



extern s32 D_800814A0;
extern u8 D_80174C8C[];
extern s32 D_80174CE0;

/* Advances the effect through growth, position tracking, and shrinkage. */
void func_80172874(void *effect, Rec_D_800E3D7C *position, S_80172874_2 *transform)
{
    void *base = effect;
    S_80172874_6 *source;
    S_80172874_3 *owner;
    s16 duration;
    s16 mode;
    s32 grow_scale;
    s32 shrink_scale;
    u16 angle;
    u16 current_mode;
    u16 next_angle;
    u16 grow_step;
    u16 shrink_step;
    u16 owner_value;
    void *parent;

    parent = ((S_80172874_0 *)base)->unk_20;
    source = ((S_80172874_0 *)base)->unk_24;
    owner = ((S_80172874_1_pre *)parent)[-1].unk_00;
    angle = transform->unk_1A;
    owner_value = owner->unk_06;
    next_angle = angle + 0x190;
    transform->unk_1A = next_angle;
    transform->unk_06 = owner_value;
    if ((u16)next_angle >= 0x1001U) {
        transform->unk_1A = angle - 0xE70;
    }

    mode = ((S_80172874_0 *)base)->unk_12.s;
    current_mode = ((S_80172874_0 *)base)->unk_12.u;
    switch (mode) {
    case 0:
        goto grow;
    case 1:
        goto track;
    case 2:
        goto shrink;
    default:
        goto done;
    }

grow:
    grow_step = ((S_80172874_0 *)base)->unk_16.s + 1;
    duration = ((S_80172874_0 *)base)->unk_18;
    grow_scale = ((s32)(grow_step << 16) >> 9) / duration;
    ((S_80172874_0 *)base)->unk_16.s = grow_step;
    transform->unk_0C = grow_scale;
    transform->unk_0D = grow_scale;
    transform->unk_0E = grow_scale;
    if (((S_80172874_0 *)base)->unk_16.u >= 5) {
        ((S_80172874_0 *)base)->unk_12.p = ((S_80172874_0 *)base)->unk_12.p + 1;
        goto done;
    }
    goto done;

track:
    {
        u32 flag_base;
        flag_base = 0x80170000;
        if (((S_80172874_4 *)flag_base)->unk_4CE0 == 0) {
            ((S_80172874_0 *)base)->unk_12.s = current_mode + 1;
            ((S_80172874_0 *)base)->unk_18 = 0x14;
            ((S_80172874_0 *)base)->unk_16.s = 0x14;
        }
        if (owner->unk_2C == D_80174C8C) {
            ((S_80172874_0 *)base)->unk_18 = 0x14;
            ((S_80172874_0 *)base)->unk_16.s = 0x14;
            ((S_80172874_0 *)base)->unk_12.s = ((S_80172874_0 *)base)->unk_12.p + 1;
        }
        position->unk_00.at00_s32.v = source->unk_00;
        position->unk_04.at00_s32.v = source->unk_04;
        position->unk_08.at00_s32.v = source->unk_08;
        goto done;
    }

shrink:
    shrink_step = ((S_80172874_0 *)base)->unk_16.s - 1;
    shrink_scale = ((s32)(shrink_step << 16) >> 9) / ((S_80172874_0 *)base)->unk_18;
    ((S_80172874_0 *)base)->unk_16.s = shrink_step;
    transform->unk_0C = shrink_scale;
    transform->unk_0D = shrink_scale;
    transform->unk_0E = shrink_scale;
    if (((S_80172874_0 *)base)->unk_16.u <= 0) {
        s32 *global_base;
        global_base = (s32 *)0x80080000;
        ((S_80172874_0_pre *)base)[-1].unk_00 |= 0x8000;
        ((S_80172874_7 *)global_base)->unk_14A0 |= 0x8000;
    }

done:
    return;
}
