#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *D_80170858[];
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s16 func_800BCB04();
M2C_UNK func_80173494() __attribute__((noreturn));
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083460;
extern s16 D_8008346A;


typedef struct S_801731FC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801731FC_0;   /* arg0 in func_801731FC */

typedef struct S_801731FC_1_pre {
    u16 unk_00;
} S_801731FC_1_pre;   /* the 0x2 bytes before arg3 in func_801731FC, addressed as arg3[-1] */

typedef struct S_801731FC_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_801731FC_1;   /* arg3 in func_801731FC */

typedef struct S_801731FC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801731FC_2;   /* arg1 in func_801731FC */

typedef struct S_801731FC_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801731FC_3;   /* arg2 in func_801731FC */

typedef struct S_801731FC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_801731FC_4;   /* global_ptr in func_801731FC */

void func_801731FC(S_801731FC_0 *arg0, S_801731FC_2 *arg1, S_801731FC_3 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK var_a2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0_2;
    u32 temp_a1;
    u32 sound_x;
    u32 sound_y;
    u8 temp_v0;
    S_801731FC_4 *global_ptr;

    temp_a1 = arg0->unk_9B;
    temp_v1 = ((u16) ((S_801731FC_1 *)arg3)->unk_6A >> 8) & 0xE;
    temp_a2 = *(s16 *)((u8 *)&D_8006CCD8 + temp_v1);
    temp_a3 = *(s16 *)((u8 *)&D_8006CCE8 + temp_v1);
    if (temp_a1 >= 5U) {
        goto block_20;
    }
    (void)jt_keep;
    goto *D_80170858[(u32)temp_a1];
jt_c0:
    {
        u32 mask_a0 = 0xF7FFFFFF;
        u32 mask_v1;
        u32 flags;
        u16 field98;

        
        field98 = arg0->unk_98;
        
        mask_v1 = 0xFFFBFFFF;
        field98 |= 8;
        arg0->unk_98 = field98;
        flags = ((S_801731FC_1 *)arg3)->unk_1C.u;
        flags &= mask_a0;
        flags &= mask_v1;
        ((S_801731FC_1 *)arg3)->unk_1C.u = flags;
        arg1->unk_0C = temp_a2 << 0x10;
        arg1->unk_10 = temp_a3 << 0x10;
        arg1->unk_14 = 0xFFF40000;
        arg0->unk_9B = arg0->unk_9B + 1;
    }
jt_c1:
    arg1->unk_14 += 0x1C000;
    if (func_800BCB04(arg1->unk_02, arg1->unk_06,
                      arg1->unk_0A, temp_a3) < 0x200) {
        goto block_5;
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
block_5:
    if (D_8008346A != 0) {
        goto block_20;
    }
    arg0->unk_9B = arg0->unk_9B + 1;
jt_c2:
    temp_v1_2 = ((S_801731FC_1 *)arg3)->unk_14;
    if (!(temp_v1_2 & 0x4000)) {
        goto block_10;
    }
    if (temp_v1_2 & 0x20000000) {
        goto block_10;
    }
    func_800ACF88(arg3);
block_10:
    func_800A56E0(0x805);
    arg2->unk_10 = 0x20;
    arg2->unk_14 |= 0xC;
    arg2->unk_12 -= 0x80;
    arg0->unk_9B = arg0->unk_9B + 1;
jt_c3:
    arg1->unk_14 += 0x1C000;
    if (!(arg2->unk_14 & 0x6000)) {
        goto block_20;
    }
    arg0->unk_96 = 0x80U;
    arg0->unk_9B = arg0->unk_9B + 1;
    func_80173494();
    return;
jt_c4:
    ((S_801731FC_1 *)arg3)->unk_1C.s |= 0x10000000;
    temp_v0 = (u8)arg0->unk_96;
    arg2->unk_0E = temp_v0;
    arg2->unk_0D = temp_v0;
    arg2->unk_0C = temp_v0;
    temp_v0_2 = arg0->unk_96 - 0x18;
    arg0->unk_96 = temp_v0_2;
    if ((s16)temp_v0_2 >= 0x18) {
        goto block_20;
    }
    global_ptr = &D_80083460;
    if (global_ptr->unk_10 != (arg3 - 0x20)) {
        goto block_17;
    }
    global_ptr->unk_10 &= 0x7FFFFFFF;
block_17:
    func_800A2FE0(arg3, temp_a1, temp_a2, temp_a3);
    func_800A32A4(arg3);
    sound_x = arg2->unk_24;
    sound_y = arg2->unk_25;
    var_a2 = 0x3000;
    if (!(((S_801731FC_1 *)arg3)->unk_1C.s & 0x2000)) {
        goto block_19;
    }
    var_a2 = 0x300;
block_19:
    func_8009A3D0(sound_x, sound_y, var_a2);
    func_8009A028(arg3);
    ((S_801731FC_1_pre *)arg3)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
block_20:
    return;
}
