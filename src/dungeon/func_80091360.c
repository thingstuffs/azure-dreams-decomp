#include "common.h"
#include "m2c_compat.h"

typedef struct S_80096AC0_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_80096AC0_0;   /* arg0 in func_80096AC0 */

void func_80096AC0(S_80096AC0_0 *arg0) {
    arg0->unk_9A = 0x34;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg0->unk_A2 = (u16) (arg0->unk_A2 & 0xFFFE);
}
