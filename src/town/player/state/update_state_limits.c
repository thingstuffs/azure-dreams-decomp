#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Input;

typedef struct {
    u8 pad[0x24];
    s32 unk24;
    u8 pad28[8];
    s32 unk30;
} State;

extern s16 map_scene_selector_alias[];
extern State player_blocking_rects;

/* Update the state limits from the input value unless mode 12 is active. */
void update_state_limits(Input *source) {
    Input *input;
    State *state_page;
    s32 input_value;

    if (map_scene_selector_alias[0] == 12) {
        return;
    }

    input = source;
    input_value = input->unk4;
    if (input_value <= 0x03FFFFFF) {
        State *state = &player_blocking_rects;

        state_page = (State *)0x80100000;
        state->unk24 = 0x0F500000;
        state->unk30 = 0x10B00000;
    } else {
        state_page = &player_blocking_rects;
        state_page->unk24 = 0x13500000 - input_value;
        state_page->unk30 = input->unk4 + 0x0CB00000;
    }
}
