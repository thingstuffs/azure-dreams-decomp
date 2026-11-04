#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/minigame/position.h"

typedef struct S_80024A30_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80024A30_1;


/* Waits for a trigger flag, then decreases the level and sets completion flags. */
void fade_scene_tile_after_completion_flag(SceneTileObject *state, s32 unused_lower_color, s32 unused_saved_upper_color, s32 unused_upper_color) {
    S_80024A30_1 *trigger;
    s16 phase;
    s32 level;

    trigger = state->linked;
    phase = state->state.s;

    switch (phase) {
    case 0:
        if (trigger->unk_0C & 2) {
            state->state.u++;
        }
        break;

    case 1:
        level = state->color + 0xFFF7F7F8U;
        state->color = level;
        if (level <= 0x80808) {
            NODE_HEADER(state)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

}
