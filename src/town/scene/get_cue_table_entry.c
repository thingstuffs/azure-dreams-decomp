#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

extern u8 scene_rows[];
extern u8 D_80019A6C[];
extern s32 selected_scene_row_index[3];

/* Return the cached blob when the cue is already playing, otherwise start it and return the state's row. */
s32 get_cue_table_entry(void) {
    s32 *indexp;
    u8 *base;
    s32 offset;
    s32 result;

    indexp = selected_scene_row_index;
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

/* MECHANISM: A 12-byte D_80019B8C declaration holds its page in retail's sole s0 save. Cdk-G0 preserves
   the retail reload and epilogue-load order. */
