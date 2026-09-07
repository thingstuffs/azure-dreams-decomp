#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800D991C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_800D991C_0;   /* arg0 in func_800D991C */





M2C_UNK func_8003DB94();        /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800D8C64;
extern void *D_800E262C[];

void func_800D991C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    void **temp_a1;
    s16 *temp_a0_2;
    u8 *temp_v0_4;
    s32 temp_a0;
    s16 temp_v0;
    s32 temp_x;
    s32 temp_x_result;
    s32 temp_y;
    s32 temp_v1_2;
    s32 temp_x_delta;
    s32 temp_y_delta;
    s32 temp_v1;

    temp_v1 = ((S_800D991C_0 *)arg0)->unk_9B;
    switch (temp_v1) {
        case 0:
            ((S_800D991C_0 *)arg0)->unk_98 = (u16) (((S_800D991C_0 *)arg0)->unk_98 | 8);
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0xFFF00000;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0xF7FFFFFF);
            ((S_800D991C_0 *)arg0)->unk_A4 = 0;
            ((S_800D991C_0 *)arg0)->unk_9B = (u8) (((S_800D991C_0 *)arg0)->unk_9B + 1);
            break;
        case 1:
            break;
        case 2:
            goto block_13;
        default:
            goto block_17;
    }
block_9:
    temp_a0 = ((S_800D991C_0 *)arg0)->unk_96;
    ((S_800D991C_0 *)arg0)->unk_90 = (s32) (((S_800D991C_0 *)arg0)->unk_90 - ((S_800D991C_0 *)arg0)->unk_A4);
    if (temp_a0 != 0) {
        temp_x = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        temp_x_delta = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        temp_x_result = (s32) ((temp_x - temp_x_delta) << 0x10) / temp_a0;
        temp_y_delta = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = temp_x_result;
        temp_y = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) ((s32) ((temp_y - temp_y_delta) << 0x10) / (s16) ((S_800D991C_0 *)arg0)->unk_96);
        ((S_800D991C_0 *)arg0)->unk_A4 = (s32) (((S_800D991C_0 *)arg0)->unk_A4 + ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32);
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = (s32) (((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 + 0x48000);
    }
    ((S_800D991C_0 *)arg0)->unk_90 = (s32) (((S_800D991C_0 *)arg0)->unk_90 + ((S_800D991C_0 *)arg0)->unk_A4);
    if (((S_800D991C_0 *)arg0)->unk_96 < 2) {
        ((S_800D991C_0 *)arg0)->unk_90 = 0;
        ((S_800D991C_0 *)arg0)->unk_98 = (u16) (((S_800D991C_0 *)arg0)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 | 0x08000000);
        ((S_800D991C_0 *)arg0)->unk_9B = (u8) (((S_800D991C_0 *)arg0)->unk_9B + 1);
    }
block_13:
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x08000000) {
        ((S_800D991C_0 *)arg0)->unk_98 = (u16) (((S_800D991C_0 *)arg0)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        temp_a1 = D_800E262C;
        (*(void **)((u8 *)arg2 + 0x2C)) = temp_a1;
        func_8003DB94(arg2, *(void **)((u8 *)temp_a1 + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C)), 0);
        ((S_800D991C_0 *)arg0)->unk_9B = (u8) (((S_800D991C_0 *)arg0)->unk_9B + 1);
    }
block_17:
    temp_v0 = (u16) ((S_800D991C_0 *)arg0)->unk_96 - 1;
    ((S_800D991C_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        temp_a0_2 = (s16 *)&D_80083460;
        if (temp_a0_2[4] != 0) {
            temp_a0_2[4] = (s16) ((u16) temp_a0_2[4] - 1);
        }
        temp_v1_2 = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
        if (temp_v1_2 & 0x2000) {
            goto block_21;
        }
        if (temp_v1_2 & 0x410) {
            goto block_21;
        }
        if (!(temp_v1_2 & 0x20000)) {
            goto block_21;
        }
        temp_v0_4 = (u8 *)&D_80082E80;
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, temp_v0_4[0x24], temp_v0_4[0x25], &sp18);
block_21:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            ((S_800D991C_0 *)arg0)->unk_8C = &D_800D8C64;
            func_800A9A04(arg3);
        }
    }
}

/* MECHANISM: The true-rowbase natural switch and local gotos preserve the 0x38-frame decision tree.
   Signed full-width loads plus one name per X/Y live range reproduce the mflo-slot load schedule.
   Held symbolic bases and three explicit flag-test edges close the addressing and tail CFG. */
