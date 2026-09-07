#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */

typedef struct S_800A6B70_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6B70_0;   /* arg0 in func_800A6B70 */

typedef struct S_800A6B70_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800A6B70_1;   /* arg2 in func_800A6B70 */

void func_800A6B70(S_800A6B70_0 *arg0, M2C_UNK arg1, S_800A6B70_1 *arg2) {
    s32 temp_v0;
    s8 temp_v0_2;

    temp_v0 = arg0->unk_0C + 1;
    arg0->unk_0C = temp_v0;
    temp_v0_2 = (func_800644B8(temp_v0 << 6) >> 7) + 0x60;
    arg2->unk_0E = temp_v0_2;
    arg2->unk_0D = temp_v0_2;
    arg2->unk_0C = temp_v0_2;
}
