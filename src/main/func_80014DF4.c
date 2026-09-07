#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026FD4();                         /* extern */

typedef struct S_80027DF4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x14];
    s32 unk_24;
} S_80027DF4_0;   /* temp_v0 in func_80027DF4 */

void func_80027DF4(s32 arg0, s32 arg1) {
    S_80027DF4_0 *temp_v0;

    if (arg0 != 0) {
        temp_v0 = arg0 + 0x20;
        temp_v0->unk_0C = arg1;
        func_80026FD4(temp_v0->unk_24);
    }
}
