#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "dungeon/effect/motion.h"
#include "slus.h"

/* Increment the linked object's counter, process the target, and propagate its status flags. */
void advance_linked_object_counter(void *entry, s32 unused, SpriteFrameState *target) {
    u8 *linked_obj;

    linked_obj = *(u8 **)((u8 *)entry + 0xC);
    *(u16 *)(linked_obj + 0x16) += 1;
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        *(u16 *)((u8 *)entry - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
