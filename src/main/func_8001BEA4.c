#include "common.h"

typedef struct S_8001BEA4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x8];
    s32 unk_20;
} S_8001BEA4_0;   /* arg0 in func_8001BEA4 */

void func_8001BEA4(S_8001BEA4_0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->unk_14 = arg1;
    arg0->unk_08 = arg2;
    arg0->unk_0C = arg3;
    arg0->unk_20 = arg4;
}
