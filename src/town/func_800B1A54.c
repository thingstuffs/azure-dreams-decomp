#include "common.h"
#include "m2c_compat.h"

s32 func_80049DE8();                        /* extern */
extern M2C_UNK D_800AE5B8;

typedef struct S_800AF1B4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
} S_800AF1B4_0;   /* temp_s0 in func_800AF1B4 */

typedef struct S_800AF1B4_1 {
    u8 pad_00[0x20];
    M2C_UNK * unk_20;
} S_800AF1B4_1;   /* arg0 in func_800AF1B4 */

/* Updates the object value and resets associated state when it changes. */
void func_800AF1B4(void *object, M2C_UNK value_arg, s32 reset_value) {
    s32 new_value;
    S_800AF1B4_0 *state;

    state = object + 0x20;
    new_value = func_80049DE8(state->unk_1C, value_arg, state->unk_28);
    if (new_value != state->unk_1C) {
        state->unk_1C = new_value;
        state->unk_04 = reset_value;
        state->unk_08 = 0;
        ((S_800AF1B4_1 *)object)->unk_20 = &D_800AE5B8;
        state->unk_20 = (s32) state->unk_1C;
    }
}
