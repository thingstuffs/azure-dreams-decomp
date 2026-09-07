#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_8009204C;
extern M2C_UNK D_800D00B0;

typedef struct S_800942B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800942B0_0;   /* arg1 in func_800942B0 */

typedef struct S_800942B0_1 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800942B0_1;   /* arg0 in func_800942B0 */

/* Initializes an object and its associated state. */
void func_800942B0(S_800942B0_1 *object, S_800942B0_0 *state, M2C_UNK initData) {
    func_800948DC();
    state->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D00B0, object, initData);
    object->unk_00 = &D_8009204C;
    object->unk_0A = 0;
}
