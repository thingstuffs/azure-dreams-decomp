#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F294();            /* extern */
M2C_UNK func_8008F664();            /* extern */
M2C_UNK func_8009EC70(); /* extern */

typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;   /* arg0 in func_8009ECF0 */

void func_8009ECF0(S_8009ECF0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    u16 temp_v0;

    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_8009EC70(arg0, arg1, arg2, arg3);
    }
}
