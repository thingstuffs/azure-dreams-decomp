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

void func_80172874(void *arg0, Rec_D_800E3D7C *arg1, S_80172874_2 *arg2)
{
    void *base = arg0;
    S_80172874_6 *source;
    S_80172874_3 *owner;
    s16 temp_a0_3;
    s16 temp_v1;
    s32 temp_lo;
    s32 temp_lo_2;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 owner_value;
    void *parent;

    parent = ((S_80172874_0 *)base)->unk_20;
    source = ((S_80172874_0 *)base)->unk_24;
    owner = ((S_80172874_1_pre *)parent)[-1].unk_00;
    temp_a0 = arg2->unk_1A;
    owner_value = owner->unk_06;
    temp_v0 = temp_a0 + 0x190;
    arg2->unk_1A = temp_v0;
    arg2->unk_06 = owner_value;
    if ((u16)temp_v0 >= 0x1001U) {
        arg2->unk_1A = temp_a0 - 0xE70;
    }

    temp_v1 = ((S_80172874_0 *)base)->unk_12.s;
    temp_a0_2 = ((S_80172874_0 *)base)->unk_12.u;
    switch (temp_v1) {
    case 0:
        goto mode_zero;
    case 1:
        goto mode_one;
    case 2:
        goto mode_two;
    default:
        goto done;
    }

mode_zero:
    temp_v1_2 = ((S_80172874_0 *)base)->unk_16.s + 1;
    temp_a0_3 = ((S_80172874_0 *)base)->unk_18;
    temp_lo = ((s32)(temp_v1_2 << 16) >> 9) / temp_a0_3;
    ((S_80172874_0 *)base)->unk_16.s = temp_v1_2;
    arg2->unk_0C = temp_lo;
    arg2->unk_0D = temp_lo;
    arg2->unk_0E = temp_lo;
    if (((S_80172874_0 *)base)->unk_16.u >= 5) {
        ((S_80172874_0 *)base)->unk_12.p = ((S_80172874_0 *)base)->unk_12.p + 1;
        goto done;
    }
    goto done;

mode_one:
    {
    u32 flag_base;
    flag_base = 0x80170000;
    if (((S_80172874_4 *)flag_base)->unk_4CE0 == 0) {
        ((S_80172874_0 *)base)->unk_12.s = temp_a0_2 + 1;
        ((S_80172874_0 *)base)->unk_18 = 0x14;
        ((S_80172874_0 *)base)->unk_16.s = 0x14;
    }
    if (owner->unk_2C == D_80174C8C) {
        ((S_80172874_0 *)base)->unk_18 = 0x14;
        ((S_80172874_0 *)base)->unk_16.s = 0x14;
        ((S_80172874_0 *)base)->unk_12.s = ((S_80172874_0 *)base)->unk_12.p + 1;
    }
    arg1->unk_00.at00_s32.v = source->unk_00;
    arg1->unk_04.at00_s32.v = source->unk_04;
    arg1->unk_08.at00_s32.v = source->unk_08;
    goto done;
    }

mode_two:
    temp_v1_3 = ((S_80172874_0 *)base)->unk_16.s - 1;
    temp_lo_2 = ((s32)(temp_v1_3 << 16) >> 9) / ((S_80172874_0 *)base)->unk_18;
    ((S_80172874_0 *)base)->unk_16.s = temp_v1_3;
    arg2->unk_0C = temp_lo_2;
    arg2->unk_0D = temp_lo_2;
    arg2->unk_0E = temp_lo_2;
    if (((S_80172874_0 *)base)->unk_16.u <= 0) {
        register s32 *global_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        global_base = (s32 *)0x80080000;
        ASM_KEEP(global_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_80172874_0_pre *)base)[-1].unk_00 |= 0x8000;
        ((S_80172874_7 *)global_base)->unk_14A0 |= 0x8000;
    }

done:
    return;
}
