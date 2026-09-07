#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C41D4();                            /* extern */

typedef struct S_800C3C28_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C3C28_0;   /* arg2 in func_800C3C28 */

void func_800C3C28(M2C_UNK arg0, M2C_UNK arg1, S_800C3C28_0 *arg2) {
    if (arg2->unk_14 & 0x6000) {
        func_800C41D4();
    }
}
