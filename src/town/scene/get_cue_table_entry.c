#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene.h"
#include "town/player/state.h"

extern u8 scene_rows[];
extern u8 D_80019A6C[];

/* Return the cached blob when the cue is already playing, otherwise start it and return the state's row. */
s32 get_cue_table_entry(void) {
    s32 *indexp;
    u8 *base;
    s32 offset;
    s32 result;

    indexp = &selected_scene_row_index;
    if (get_script_flag_mask(*indexp + 0x147A) != 0) {
        result = (s32)D_80019A6C;
    } else {
        set_script_flag_bit(*indexp + 0x147A);
        base = scene_rows;
        offset = *indexp * 0x18;
        result = *(s32 *)(base + offset);
    }
    return result;
}

/* The index address is kept across the flag calls for the reload that selects the row. */
