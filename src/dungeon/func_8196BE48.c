#include "common.h"

typedef struct S_8196BE48_0_pre {
    u16 unk_00;
} S_8196BE48_0_pre;   /* the 0x2 bytes before obj in func_8196BE48, addressed as obj[-1] */

typedef struct S_8196BE48_0 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x6];
    u16 unk_34;
    u8 pad_36[0xA];
    u8 unk_40;
    u8 unk_41;
    u8 pad_42[0xE];
    u16 unk_50;
} S_8196BE48_0;   /* obj in func_8196BE48 */

typedef struct S_8196BE48_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8196BE48_1;   /* arg2 in func_8196BE48 */



extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196BE48(void *arg0, s32 arg1, void *arg2) {
    u8 *obj = arg0;
    u8 *page = (u8 *)&D_800269B4 - 0x69B4;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    ((S_8196BE48_0 *)obj)->unk_2C = (u16)(((S_8196BE48_0 *)obj)->unk_2C - 1);
    ((S_8196BE48_1 *)arg2)->unk_1C = (u16)(((S_8196BE48_1 *)arg2)->unk_1C + 0x7C);
    ((S_8196BE48_1 *)arg2)->unk_1E = (u16)(((S_8196BE48_1 *)arg2)->unk_1E + 0x54);
    temp_v0 = ((S_8196BE48_0 *)obj)->unk_34 + 1;
    *(s16 *)(page + 0x69B4) = 1;
    ((S_8196BE48_0 *)obj)->unk_34 = temp_v0;
    if ((s16)temp_v0 == 3) {
        temp_v0_2 = ((S_8196BE48_0 *)obj)->unk_50 + 1;
        ((S_8196BE48_0 *)obj)->unk_50 = temp_v0_2;
        if ((s16)temp_v0_2 < 7) {
            ((S_8196BE48_0 *)obj)->unk_34 = 0;
            temp_v0_3 = ((S_8196BE48_0 *)obj)->unk_40 + 0x18;
            ((S_8196BE48_0 *)obj)->unk_40 = temp_v0_3;
            if ((temp_v0_3 & 0xFF) == 0x60) {
                ((S_8196BE48_0 *)obj)->unk_40 = 0;
                ((S_8196BE48_0 *)obj)->unk_41 = (u8)(((S_8196BE48_0 *)obj)->unk_41 + 0x20);
            }
        }
    }
    if ((s16)((S_8196BE48_0 *)obj)->unk_2C <= 0) {
        (*(u16 *)((u8 *)obj + -2)) = (u16)(((S_8196BE48_0_pre *)obj)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
