#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B0C68();                      /* extern */

typedef struct S_800B17C0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17C0_0;   /* temp_a0 in func_800B17C0 */

void func_800B17C0(s32 arg0, s32 arg1) {
    S_800B17C0_0 *temp_a0;

    temp_a0 = arg0 + 0x20;
    temp_a0->unk_08 = arg1;
    func_800B0C68(temp_a0);
}
