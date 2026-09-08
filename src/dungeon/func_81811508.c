#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026370();                    /* extern */
s32 func_80026388();               /* extern */

typedef struct S_80026508_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0x5C];
    s32 unk_70;
} S_80026508_0;   /* temp_s0 in func_80026508 */

/* Update the embedded state value through a table lookup and propagate the result. */
void func_80026508(s32 object_addr) {
    s32 updated_value;
    S_80026508_0 *state;

    state = object_addr + 0x20;
    updated_value = func_80026388(-1, state->unk_08, state->unk_10);
    state->unk_08 = updated_value;
    func_80026370(state->unk_70, updated_value);
}
