#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026FD4();                         /* extern */

typedef struct S_80027DF4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x14];
    s32 unk_24;
} S_80027DF4_0;   /* temp_v0 in func_80027DF4 */

/* Sets an object's state value and passes its linked value to func_80026FD4. */
void func_80027DF4(s32 object_addr, s32 state_value) {
    S_80027DF4_0 *state;

    if (object_addr != 0) {
        state = object_addr + 0x20;
        state->unk_0C = state_value;
        func_80026FD4(state->unk_24);
    }
}
