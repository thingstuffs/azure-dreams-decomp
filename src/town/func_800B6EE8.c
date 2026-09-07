#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B4648_1 {
    u8 pad_00[0x18];
    s32 * unk_18;
    u8 pad_1C[0x2C];
    s32 * unk_48;
} S_800B4648_1;   /* (temp_s0 + arg0->unk_5C) in func_800B4648 */


M2C_UNK func_8004E99C();                         /* extern */

typedef struct S_800B4648_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800B4648_0;   /* arg0 in func_800B4648 */

void func_800B4648(S_800B4648_0 *arg0) {
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s1;

    var_s1 = 0;
    do {
        temp_s0 = var_s1 * 4;
        temp_a0 = *((S_800B4648_1 *)((temp_s0 + arg0->unk_5C)))->unk_18;
        var_s1 += 1;
        func_8004E99C(temp_a0);
        func_8004E99C(*((S_800B4648_1 *)((temp_s0 + arg0->unk_5C)))->unk_48);
    } while (var_s1 < 5);
}
