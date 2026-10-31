#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/minigame/position.h"

   /* the 0x2 bytes before arg0 in fade_scene_tile_after_completion_flag, addressed as arg0[-1] */


typedef struct S_80024A30_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80024A30_1;


/* Waits for a trigger flag, then decreases the level and sets completion flags. */
void fade_scene_tile_after_completion_flag(void *state_arg) {
    SceneTileObject *state = state_arg;
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
            ((ObjectStatusPrefix16 *)state)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

}
