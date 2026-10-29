#include "common.h"
#include "town/scene.h"

extern u8 scene_rows[];
extern u8 D_80019A6C[];
extern s32 selected_scene_row_index[3];

extern void func_800193E0(s32);
extern s32 func_800194D8(s32);

/* Return the cached blob when the cue is already playing, otherwise start it and return the state's row. */
s32 get_cue_table_entry(void) {
    s32 *indexp;
    u8 *base;
    s32 offset;
    s32 result;

    indexp = selected_scene_row_index;
    if (func_800194D8(*indexp + 0x147A) != 0) {
        result = (s32)D_80019A6C;
    } else {
        func_800193E0(*indexp + 0x147A);
        base = scene_rows;
        offset = *indexp * 0x18;
        result = *(s32 *)(base + offset);
    }
    return result;
}

/* MECHANISM: A 12-byte D_80019B8C declaration holds its page in retail's sole s0 save. Cdk-G0 preserves
   the retail reload and epilogue-load order. */
