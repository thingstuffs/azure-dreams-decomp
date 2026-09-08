#include "common.h"

typedef struct S_80026FB0_0 {
    u8 pad_00[0x64];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
} S_80026FB0_0;   /* arg0 in func_80026FB0 */

typedef struct S_80026FB0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80026FB0_1;   /* arg2 in func_80026FB0 */



extern s32 D_800814A0;

void func_80026FB0(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 timer;
    s32 value;

    state = ((S_80026FB0_0 *)arg0)->unk_64.s;
    switch (state) {
    default:
        return;

    case 0:
        timer = (u16)((S_80026FB0_0 *)arg0)->unk_66 - 1;
        ((S_80026FB0_0 *)arg0)->unk_66 = timer;
        if ((timer << 16) <= 0) {
            ((S_80026FB0_0 *)arg0)->unk_66 = 0x10;
            ((S_80026FB0_0 *)arg0)->unk_64.u += 1;
        }
        break;

    case 1:
        value = ((S_80026FB0_1 *)arg2)->unk_0C;
        value = value + ((0x80 - value) / ((S_80026FB0_0 *)arg0)->unk_66);
        ((S_80026FB0_1 *)arg2)->unk_0C = value;
        ((S_80026FB0_1 *)arg2)->unk_0E = value;
        ((S_80026FB0_1 *)arg2)->unk_0D = value;
        timer = (u16)((S_80026FB0_0 *)arg0)->unk_66 - 1;
        ((S_80026FB0_0 *)arg0)->unk_66 = timer;
        if ((timer << 16) <= 0) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    }
}
