#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8();                     /* extern */

typedef struct S_800C2C80_0 {
    u8 pad_00[0x92];
    u8 unk_92;
} S_800C2C80_0;   /* arg0 in func_800C2C80 */

void func_800C2C80(S_800C2C80_0 *arg0, M2C_UNK arg1) {
    if (arg0->unk_92 == 0) {
        func_800478B8(arg1);
    }
}
