#include "common.h"
#include "m2c_compat.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
extern u16 D_80083462;

typedef struct S_801754F0_0 {
    u8 pad_00[0x6D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801754F0_0;   /* arg3 in func_801754F0 */

typedef struct S_801754F0_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_801754F0_1;   /* arg0 in func_801754F0 */

void func_801754F0(S_801754F0_1 *arg0, M2C_UNK arg1, M2C_UNK arg2, S_801754F0_0 *arg3) {
    arg3->unk_71 = (u8) (arg3->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        arg0->unk_8C = 0;
        arg0->unk_9A = 0x17;
        arg0->unk_9B = 0;
        arg0->unk_96 = 0;
        func_800A4ACC(arg3);
        arg3->unk_6D = (u8) (arg3->unk_6D - 1);
    }
}
