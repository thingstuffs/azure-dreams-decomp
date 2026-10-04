#include "common.h"
#include "shared/game_work.h"


typedef struct State {
    s32 unk0;
    s32 unk4;
    s32 flags;
} State;

void func_80091000(s32 *, s32, s32);
void func_80093D48();

/* Calls func_80093D48 if func_80091000 leaves the value unchanged and flag 0x20 is clear. */
void func_800911D4(s32 *value, s32 input_a, s32 input_b) {
    GameWork *state;
    s32 old_value;

    state = &gameWork;
    old_value = *value;
    func_80091000(value, input_a, input_b);
    if ((old_value == *value) && !(state->buttons & 0x20)) {
        func_80093D48(value, input_a, input_b);
    }
}
