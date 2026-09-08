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

/* Sets two fields in the object's embedded state and invokes their handlers. */
void func_800B1778(s32 object_addr, s32 value_10, s32 value_08) {
    S_800B1778_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = value_08;
    func_800B173C(state);
    state->unk_10 = value_10;
    func_800B0FD4(state);
}
