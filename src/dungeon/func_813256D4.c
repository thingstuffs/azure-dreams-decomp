#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_800AD9B4();            /* extern */
extern M2C_UNK D_8016B778;

typedef struct S_8016CED4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_8016CED4_0;   /* arg0 in func_8016CED4 */


s32 func_800AB378(S_8016CED4_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
void func_8016CED4(S_8016CED4_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    if (func_800AB378(arg0, arg1, arg2, arg3) != 0) {
        func_800AD9B4(arg2, arg3);
        arg0->unk_8C = &D_8016B778;
    }
}
