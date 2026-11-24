#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/orbit_burst_spell.h"
#include "slus.h"

/* Increment the linked object's counter, process the target, and propagate its status flags. */
void advance_linked_object_counter(LinkedCounterSpriteBody *entry, ObjectPosition *unused, SpriteFrameState *target) {
    entry->owner->busy += 1;
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        NODE_HEADER(entry)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
