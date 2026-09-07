#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D34CC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D34CC_0;   /* arg0 in func_800D34CC */

typedef struct S_800D34CC_1_pre {
    u16 unk_00;
} S_800D34CC_1_pre;   /* the 0x2 bytes before arg3 in func_800D34CC, addressed as arg3[-1] */

typedef struct S_800D34CC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800D34CC_1;   /* arg3 in func_800D34CC */

typedef struct S_800D34CC_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; volatile u8 v; } at02; struct { u8 pad[0x2]; u8 v; } at02u; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_800D34CC_2;   /* arg2 in func_800D34CC */

typedef struct S_800D34CC_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D34CC_3;   /* var_v0 in func_800D34CC */


s32 func_80042900();                 /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A32A4(void *);                 /* extern */
M2C_UNK func_800A56C0();                            /* extern */
M2C_UNK func_800A56E0();                     /* extern */
void func_800D36B4(s32);                     /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;
extern s16 D_8008346A;

void func_800D34CC(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_v0;
    M2C_UNK var_a2;
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 temp_a1;
    s16 temp_v0_2;
    s32 temp_dim;
    s32 temp_dim2;
    s32 temp_green;
    s32 temp_v1_4;
    u8 temp_a0_2;
    u8 temp_a1_2;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;

    temp_v1 = ((S_800D34CC_0 *)arg0)->unk_9B;
    if (temp_v1 != 0) {
        temp_a0 = 0x20;
        if (temp_v1 != 1) {
            func_800D36B4(temp_a0);
            return;
        }
        goto block_6;
    }
    if (D_8008346A == 0) {
        ((S_800D34CC_1 *)arg3)->unk_1C = (s32) (((S_800D34CC_1 *)arg3)->unk_1C | 0x10000000);
        func_800A56E0(0x805);
        ((S_800D34CC_2 *)arg2)->unk_0C.at00.v = 0x808080;
        ((S_800D34CC_0 *)arg0)->unk_96 = 0x10;
        ((S_800D34CC_0 *)arg0)->unk_9B = (u8) (((S_800D34CC_0 *)arg0)->unk_9B + 1);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_a0 = 0x20;
block_6:
        temp_v1_2 = (u8) ((S_800D34CC_2 *)arg2)->unk_0C.at00.v;
        ((S_800D34CC_2 *)arg2)->unk_0C.at00u.v = (u8) (temp_v1_2 + ((temp_a0 - temp_v1_2) / (s16) ((S_800D34CC_0 *)arg0)->unk_96));
        temp_v1_3 = ((S_800D34CC_2 *)arg2)->unk_0C.at01.v;
        temp_a1 = ((S_800D34CC_0 *)arg0)->unk_96;
        temp_green = temp_v1_3 + ((temp_a0 - temp_v1_3) / temp_a1);
        temp_v0 = ((S_800D34CC_2 *)arg2)->unk_0C.at02.v;
        ((S_800D34CC_2 *)arg2)->unk_0C.at01.v = (u8) temp_green;
        ((S_800D34CC_2 *)arg2)->unk_0C.at02u.v = (u8) (temp_v0 + ((temp_a0 - temp_v0) / (s16) ((S_800D34CC_0 *)arg0)->unk_96));
        temp_dim = ((S_800D34CC_2 *)arg2)->unk_1C;
        ((S_800D34CC_2 *)arg2)->unk_1C = (u16) (temp_dim - (temp_dim / (s16) ((S_800D34CC_0 *)arg0)->unk_96));
        temp_dim2 = ((S_800D34CC_2 *)arg2)->unk_1E;
        ((S_800D34CC_2 *)arg2)->unk_1E = (u16) (temp_dim2 - (temp_dim2 / (s16) ((S_800D34CC_0 *)arg0)->unk_96));
        temp_v0_2 = (u16) ((S_800D34CC_0 *)arg0)->unk_96 - 1;
        ((S_800D34CC_0 *)arg0)->unk_96 = temp_v0_2;
        if (((temp_v0_2 << 0x10) <= 0) || ((((S_800D34CC_2 *)arg2)->unk_14 & 0x8000) != 0)) {
            var_v0 = &D_80083460;
            temp_v1_4 = ((S_800D34CC_3 *)var_v0)->unk_10;
            if (temp_v1_4 == (arg3 - 0x20)) {
                ((S_800D34CC_3 *)var_v0)->unk_10 = (s32) (temp_v1_4 & 0x7FFFFFFF);
            }
            func_800A32A4(arg3);
            if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                temp_a0_2 = ((S_800D34CC_2 *)arg2)->unk_24;
                temp_a1_2 = ((S_800D34CC_2 *)arg2)->unk_25;
                var_a2 = 0x3000;
                if (((S_800D34CC_1 *)arg3)->unk_1C & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_a1_2, var_a2);
            }
            func_8009A028(arg3);
            (*(u16 *)((u8 *)arg3 + -2)) = (u16) (((S_800D34CC_1_pre *)arg3)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
            func_800A56C0();
        }
    }
}

/* MECHANISM: The four-argument ABI yields s0=arg0, s1=arg2, and s2=arg3 in the retail 0x20 frame.
   Split byte/halfword RMWs and one held &D_80083460 base reproduce the widths, live ranges, and CFG.
   Naming the final two byte arguments fills the lw delay slot and removes the +1 displacement cascade. */
