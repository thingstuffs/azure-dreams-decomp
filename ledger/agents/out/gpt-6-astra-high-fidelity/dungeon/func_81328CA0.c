#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801704A0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801704A0_0;   /* arg0 in func_801704A0 */





M2C_UNK func_80047784();
s32 func_800644B8();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
s32 func_800AD9B4();
typedef struct {
    u8 pad[0x24];
    u8 x;
    u8 y;
} Global82E80;
typedef struct {
    u8 pad[8];
    s16 count;
} Global83460;
extern Global82E80 D_80082E80;
extern s16 D_80083228[5];
extern Global83460 D_80083460;
extern u8 D_8016F78C[];
extern u8 D_80174A2C[];

void func_801704A0(S_801704A0_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    M2C_UNK sp18;
    s32 temp_a0;
    s32 temp_count;
    s32 temp_div;
    s32 temp_flag46;
    s32 temp_pos;
    s32 temp_v1_3;
    u16 temp_v0;
    s32 temp_v1;
    Global82E80 *temp_82E80;
    Global83460 *temp_83460;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto block_ge2;
    }
    if (temp_v1 == 0) {
        goto block_zero;
    }
    goto block_19;
block_ge2:
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_three;
    }
    goto block_19;
block_zero:
    arg0->unk_98 = (u16) (arg0->unk_98 | 8);
    arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 & 0xF7FFFFFF);
    arg0->unk_9E.s = 5;
    arg0->unk_A4 = 0;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
block_10:
    temp_a0 = arg0->unk_9E.s;
    arg0->unk_90 = (s32) (arg0->unk_90 - arg0->unk_A4);
    if (temp_a0 != 0) {
        s32 temp_coord;
        temp_div = arg2->unk_24;
        
        temp_coord = arg1->unk_00.at02_s16.v;
        temp_div <<= 6;
        temp_coord -= 0x20;
        
        temp_div = (s32) ((temp_div - temp_coord) << 0x10) / temp_a0;
        temp_v1_3 = arg1->unk_04.at02_s16.v - 0x20;
        arg1->unk_0C.as_s32 = temp_div;
        arg1->unk_10.at00_s32.v = (s32) ((s32) (((arg2->unk_25 << 6) - temp_v1_3) << 0x10) / (s16) arg0->unk_9E.s);
        arg0->unk_A4 = (s32) ((0 - func_800644B8(arg0->unk_9E.s * 0x199)) << 0xA);
    }
    temp_pos = arg0->unk_90;
    temp_pos += arg0->unk_A4;
    temp_count = arg0->unk_9E.u - 1;
    
    
    arg0->unk_9E.s = temp_count;
    arg0->unk_90 = temp_pos;
    if ((temp_count << 0x10) < 0) {
        arg0->unk_90 = 0;
        arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
        arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 | 0x08000000);
        arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    }
block_14:
    if (!(arg3->unk_1C.as_s32 & 0x08000000)) {
        goto block_19;
    }
    arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    arg0->unk_9B = arg0->unk_9B + 1;
    goto block_19;
block_three:
    if (arg2->unk_2C.as_pu8 != D_80174A2C) {
        arg2->unk_2C.as_pu8 = D_80174A2C;
        func_80047784(arg2, D_80174A2C[((s32) (D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    }
block_19:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800A4ACC(arg3);
        temp_83460 = &D_80083460;
        if (temp_83460->count != 0) {
            temp_83460->count = (u16) temp_83460->count - 1;
        }
        temp_v1_3 = arg3->unk_1C.as_s32;
        if (!(temp_v1_3 & 0x2000)) {
            goto block_no_2000;
        }
        temp_flag46 = arg3->unk_44.at02_u16.v;
        if (!(temp_flag46 & 0x8000)) {
            goto block_29;
        }
        arg3->unk_44.at02_u16.v = temp_flag46 & 0x7FFF;
        goto block_29;
block_no_2000:
        if (temp_v1_3 & 0x410) {
            goto block_29;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_29;
        }
        temp_82E80 = &D_80082E80;
        arg3->unk_2A.as_s16 = func_800A0818(arg2->unk_24, arg2->unk_25, temp_82E80->x, temp_82E80->y, &sp18);
block_29:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            arg0->unk_8C = D_8016F78C;
            func_800A9A04(arg3);
        }
    }
}
