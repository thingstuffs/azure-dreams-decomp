#include "common.h"
#include "m2c_compat.h"

typedef struct S_801730A4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_801730A4_0;   /* arg3 in func_801730A4 */

typedef struct S_801730A4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_801730A4_1;   /* arg0 in func_801730A4 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E2378;

void func_801730A4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((S_801730A4_0 *)arg3)->unk_71 = (u8) (((S_801730A4_0 *)arg3)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            ((S_801730A4_1 *)arg0)->unk_8C = 0;
            ((S_801730A4_1 *)arg0)->unk_9A = 0x11;
            ((S_801730A4_1 *)arg0)->unk_9B = 0;
            ((S_801730A4_0 *)arg3)->unk_6D = (u8) (((S_801730A4_0 *)arg3)->unk_6D - 1);
            ((S_801730A4_1 *)arg0)->unk_98 = (u16) (((S_801730A4_1 *)arg0)->unk_98 & 0xFFF7);
            ((S_801730A4_0 *)arg3)->unk_1C = (s32) (((S_801730A4_0 *)arg3)->unk_1C & 0xFFFBFFFF);
            (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_800E2378;
            func_80047784(arg2, *((((s32) (D_80083228 + ((S_801730A4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7) + &D_800E2378), 0);
            func_8009C93C(arg3, arg2, ((S_801730A4_0 *)arg3)->unk_2A, 1, 0);
            ((S_801730A4_0 *)arg3)->unk_84 = 0x7C;
            ((S_801730A4_0 *)arg3)->unk_85 = 0;
        }
    }
}
