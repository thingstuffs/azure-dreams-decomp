#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800381A4_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x4];
    u16 unk_18;
} S_800381A4_0;   /* arg0 in func_800381A4 */


extern M2C_UNK func_80038A10;

void func_800381A4(S_800381A4_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_18 - 1;
    arg0->unk_18 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_10 = &func_80038A10;
    }
}
