#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173D40_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173D40_0;   /* arg0 in func_80173D40 */

typedef struct S_80173D40_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80173D40_1;   /* arg2 in func_80173D40 */

typedef struct S_80173D40_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80173D40_2;   /* arg3 in func_80173D40 */

void func_80173D40(S_80173D40_0 *arg0, M2C_UNK arg1, S_80173D40_1 *arg2, S_80173D40_2 *arg3) {
    arg0->unk_9A = 0x19;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
    arg0->unk_96 = 0;
    arg3->unk_1C = (s32) (arg3->unk_1C | 0x10000000);
}
