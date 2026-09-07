#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B09EC();                 /* extern */

typedef struct S_800B17E4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17E4_0;   /* temp_a0 in func_800B17E4 */

void func_800B17E4(s32 arg0) {
    S_800B17E4_0 *temp_a0;

    temp_a0 = arg0 + 0x20;
    func_800B09EC(temp_a0, temp_a0->unk_08);
}
