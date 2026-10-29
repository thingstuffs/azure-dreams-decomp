#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "dungeon/effect/mesh.h"
#include "slus.h"

/*
 * Increments the linked object's counter and advances sprite animation; flags removal when the
 * sprite reports 0x6000.
 */
void handle_increment_s_counter_update_state_propagate_status_flags(void *object_slot, s32 unused, SpriteFrameState *state) {
    u8 *object;

    object = *(u8 **)((u8 *)object_slot + 0x0);
    *(u16 *)(object + 0x1A) += 1;
    advance_sprite_animation_and_textures(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)object_slot - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
