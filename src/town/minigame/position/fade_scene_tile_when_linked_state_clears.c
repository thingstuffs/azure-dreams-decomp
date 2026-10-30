#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/position.h"


typedef struct S_80023F6C_1 {
    s16 unk_00;
} S_80023F6C_1;   /* object in fade_scene_tile_when_linked_state_clears */


/* Wait for the linked object to clear, then reduce the level and set completion flags. */
void fade_scene_tile_when_linked_state_clears(SceneTileObject *entry) {
    S_80023F6C_1 *object;
    s32 state;
    u16 prev_state;
    s32 level;

    object = entry->linked;
    state = entry->state.s;
    prev_state = entry->state.u;

    switch (state) {
    case 0:
        if (object->unk_00 == 0) {
            entry->state.u = prev_state + 1;
        }
        break;

    case 1:
        level = entry->color + 0xFFF7F7F8U;
        entry->color = level;
        if (level <= 0x80808) {
            (*(u16 *)((u8 *)entry + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;

    default:
        break;
    }

             /* Retains the register allocation required for a byte-exact match. */
}
