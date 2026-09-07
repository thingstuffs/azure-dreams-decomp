#include "common.h"

typedef struct S_80172D88_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x19];
    u8 unk_B5;
} S_80172D88_0;   /* arg0 in func_80172D88 */

typedef struct S_80172D88_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172D88_1;   /* arg3 in func_80172D88 */



extern s32 func_8009C93C();
extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80175F44();
extern u16 D_80083462;

void func_80172D88(S_80172D88_0 *arg0, s32 arg1, s32 arg2, void *arg3)
{
    if (arg0->unk_B5 == 0) {
        ((S_80172D88_1 *)arg3)->unk_71 &= 0x7F;
        if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 16) == 0)) {
            func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 16) == 0) {
                arg0->unk_8C = 0;
                arg0->unk_9A = 0x11;
                arg0->unk_9B = 0;
                arg0->unk_96 = 0;
                ((S_80172D88_1 *)arg3)->unk_6D--;
                arg0->unk_98 |= 8;
                func_8009C93C(arg3, arg2, ((S_80172D88_1 *)arg3)->unk_2A, 1, 0);
                ((S_80172D88_1 *)arg3)->unk_84 = 0x7C;
                ((S_80172D88_1 *)arg3)->unk_85 = 0;
                return;
            }
        }
    } else {
        func_80175F44(arg0, arg1, arg2, 1, 1);
    }
}
