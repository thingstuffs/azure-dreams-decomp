#include "common.h"
#include "m2c_compat.h"

typedef struct S_80097C50_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80097C50_0;   /* arg0 in func_80097C50 */

typedef struct S_80097C50_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80097C50_1;   /* arg3 in func_80097C50 */

void func_80097C50(S_80097C50_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, S_80097C50_1 *arg3) {
    arg0->unk_9A = 0x3A;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg0->unk_96 = 0;
    arg3->unk_1C = (s32) (arg3->unk_1C & ~0x20);
}
