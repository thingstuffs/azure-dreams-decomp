#include "common.h"
#include "slus/imports.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/motion.h"

/* Installed by create_effect_sprite_at in the bank loaded from +0x186a800. */
void advance_and_retire_finished_effect(void *body, ObjectPosition *position, SpriteFrameState *sprite) {
    advance_sprite_animation_and_textures(sprite);
    if (sprite->flags & 0x6000) {
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
