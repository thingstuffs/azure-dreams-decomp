#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CAA94_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_800CAA94_0;   /* arg0 in func_800CAA94 */

void func_800CAA94(S_800CAA94_0 *arg0) {
    arg0->unk_9A = 8;
    arg0->unk_96 = 0x40;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg0->unk_1C = (s32) ((arg0->unk_1C | 0x04000000) & ~0x1638);
}
