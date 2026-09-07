#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_808138C0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_808138C0_0;   /* temp_v0 in func_808138C0 */

typedef struct S_808138C0_1 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_808138C0_1;   /* temp_a0 in func_808138C0 */

typedef struct S_808138C0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_808138C0_2;   /* ((S_808138C0_0 *)temp_v0)->unk_08 in func_808138C0 */



extern void *func_800373DC();
extern void func_8003BC18();
extern u8 D_8003C558[12];
extern u8 D_8052F210[];
extern u8 D_80284430[];
extern s32 D_80284434[];

void func_808138C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    S_808138C0_1 *temp_a0;
    S_808138C0_0 *temp_v0;
    s32 temp_v1;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = (s32)D_8052F210;
        func_8003BC18(temp_v0, D_8003C558);
        temp_a0 = temp_v0->unk_0C;
        ((S_808138C0_2 *)(temp_v0->unk_08))->unk_00 = arg1;
        ((S_808138C0_2 *)(temp_v0->unk_08))->unk_04 = arg2;
        ((S_808138C0_2 *)(temp_v0->unk_08))->unk_08 = arg3;
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        temp_a0->unk_00 = (s32)D_80284430;
        temp_v1 = D_80284434[0];
        temp_a0->unk_04 = 0;
        temp_a0->unk_05 = 0;
        temp_a0->unk_0C = arg0;
        temp_a0->unk_08 = temp_v1;
        if (arg0 != 0x808080) {
            if (arg0 == 0xF0F0F0) {
                temp_a0->unk_10 = 0x60;
                ((S_808138C0_2 *)(temp_v0->unk_08))->unk_14 = 0xFFF00000;
                goto block_4;
            }
        } else {
block_4:
            temp_a0->unk_14 = temp_a0->unk_14 | 0xC;
        }
    }
}
