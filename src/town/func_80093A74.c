#include "common.h"

typedef u32 M2C_UNK;

typedef struct State {
    s32 unk0;
    s32 unk4;
    s32 flags;
} State;

M2C_UNK func_80091000(s32 *, M2C_UNK, M2C_UNK);
M2C_UNK func_80093D48();
extern State D_80083160;

/* Calls func_80093D48 if func_80091000 leaves the value unchanged and flag 0x20 is clear. */
void func_800911D4(s32 *value, M2C_UNK input_a, M2C_UNK input_b) {
    State *state;
    s32 old_value;

    state = &D_80083160;
    old_value = *value;
    func_80091000(value, input_a, input_b);
    if ((old_value == *value) && !(state->flags & 0x20)) {
        func_80093D48(value, input_a, input_b);
    }
}
