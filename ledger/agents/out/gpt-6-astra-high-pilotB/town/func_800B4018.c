#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B0FD4();                      /* extern */
M2C_UNK func_800B173C();                      /* extern */

typedef struct S_800B1778_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B1778_0;   /* temp_s0 in func_800B1778 */

/* Set and apply two values in the object's embedded state. */
void func_800B1778(s32 object_addr, s32 field_10_value, s32 field_08_value) {
    S_800B1778_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = field_08_value;
    func_800B173C(state);
    state->unk_10 = field_10_value;
    func_800B0FD4(state);
}
