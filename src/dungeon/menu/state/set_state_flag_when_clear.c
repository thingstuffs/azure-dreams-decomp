#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu/state.h"

extern s32 dungeon_menu_object;

typedef struct S_800DBF5C_0 {
    u8 pad_00[0x54];
    s32 unk_54;
    u8 pad_58[0x4];
    s32 unk_5C;
} S_800DBF5C_0;

/* Sets the low flag bit when the state check field is zero. */
void set_state_flag_when_clear(void) {
    S_800DBF5C_0 *state;

    state = dungeon_menu_object + 0x20;
    if (state->unk_5C == 0) {
        state->unk_54 = (s32) (state->unk_54 | 1);
    }
}
