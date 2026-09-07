#include "common.h"

typedef u32 M2C_UNK;

typedef struct State {
    s32 unk0;
    s32 unk4;
    s32 flags;
} State;

M2C_UNK func_80091000();
M2C_UNK func_80093D48();
extern State D_80083160;

void func_800911D4(s32 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    State *state;
    s32 temp_s0;

    state = &D_80083160;
    temp_s0 = *arg0;
    func_80091000();
    if ((temp_s0 == *arg0) && !(state->flags & 0x20)) {
        func_80093D48(arg0, arg1, arg2);
    }
}
