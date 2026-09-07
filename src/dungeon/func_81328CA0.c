#include "common.h"
#include "m2c_compat.h"

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

typedef struct S_801704A0_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801704A0_1;   /* arg3 in func_801704A0 */

typedef struct S_801704A0_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801704A0_2;   /* arg2 in func_801704A0 */

typedef struct S_801704A0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801704A0_3;   /* arg1 in func_801704A0 */


M2C_UNK func_80047784();
s32 func_800644B8();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
s32 func_800AD9B4();
void func_801706C0(void) __attribute__((noreturn));
void func_8017078C() __attribute__((noreturn));
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

void func_801704A0(S_801704A0_0 *arg0, S_801704A0_3 *arg1, S_801704A0_2 *arg2, S_801704A0_1 *arg3) {
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
    func_801706C0();
block_ge2:
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_three;
    }
    func_801706C0();
block_zero:
    arg0->unk_98 = (u16) (arg0->unk_98 | 8);
    arg3->unk_1C = (s32) (arg3->unk_1C & 0xF7FFFFFF);
    arg0->unk_9E.s = 5;
    arg0->unk_A4 = 0;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
block_10:
    temp_a0 = arg0->unk_9E.s;
    arg0->unk_90 = (s32) (arg0->unk_90 - arg0->unk_A4);
    if (temp_a0 != 0) {
        s32 temp_coord;
        temp_div = arg2->unk_24;
        
        temp_coord = arg1->unk_02;
        temp_div <<= 6;
        temp_coord -= 0x20;
        
        temp_div = (s32) ((temp_div - temp_coord) << 0x10) / temp_a0;
        temp_v1_3 = arg1->unk_06 - 0x20;
        arg1->unk_0C = temp_div;
        arg1->unk_10 = (s32) ((s32) (((arg2->unk_25 << 6) - temp_v1_3) << 0x10) / (s16) arg0->unk_9E.s);
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
        arg3->unk_1C = (s32) (arg3->unk_1C | 0x08000000);
        arg0->unk_9B = (u8) (arg0->unk_9B + 1);
    }
block_14:
    if (!(arg3->unk_1C & 0x08000000)) {
        goto block_19;
    }
    arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    arg0->unk_9B = arg0->unk_9B + 1;
    func_801706C0();
block_three:
    if (arg2->unk_2C != D_80174A2C) {
        arg2->unk_2C = D_80174A2C;
        func_80047784(arg2, D_80174A2C[((s32) (D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7], 0);
    }
block_19:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800A4ACC(arg3);
        temp_83460 = &D_80083460;
        if (temp_83460->count != 0) {
            temp_83460->count = (u16) temp_83460->count - 1;
        }
        temp_v1_3 = arg3->unk_1C;
        if (!(temp_v1_3 & 0x2000)) {
            goto block_no_2000;
        }
        temp_flag46 = arg3->unk_46;
        if (!(temp_flag46 & 0x8000)) {
            goto block_29;
        }
        arg3->unk_46 = temp_flag46 & 0x7FFF;
        func_8017078C(temp_83460);
block_no_2000:
        if (temp_v1_3 & 0x410) {
            goto block_29;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_29;
        }
        temp_82E80 = &D_80082E80;
        arg3->unk_2A = func_800A0818(arg2->unk_24, arg2->unk_25, temp_82E80->x, temp_82E80->y, &sp18);
block_29:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            arg0->unk_8C = D_8016F78C;
            func_800A9A04(arg3);
        }
    }
}
