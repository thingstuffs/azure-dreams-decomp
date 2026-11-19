#include "common.h"
#include "slus/town_map_selection_data.h"
#include "town/data.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Input;


/* Adjust the inner X edges of the third and fourth blocking rectangles outside mode 12. */
void update_state_limits(Input *source) {
    Input *input;
    s32 input_value;

    if ((s16)map_scene_selector_alias == 12) {
        return;
    }

    input = source;
    input_value = input->unk4;
    if (input_value <= 0x03FFFFFF) {
        player_blocking_rects[9] = 0x0F500000;
        player_blocking_rects[12] = 0x10B00000;
    } else {
        player_blocking_rects[9] = 0x13500000 - input_value;
        player_blocking_rects[12] = input->unk4 + 0x0CB00000;
    }
}
