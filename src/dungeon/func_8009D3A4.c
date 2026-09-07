#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A2B04_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A2B04_0;   /* arg0 in func_800A2B04 */

void func_800A2B04(S_800A2B04_0 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_02 = (s16) (((s32) (arg1 << 0x10) >> 0xA) + 0x20);
    arg0->unk_06 = (s16) (((s32) (arg2 << 0x10) >> 0xA) + 0x20);
}
