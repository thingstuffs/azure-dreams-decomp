#include "common.h"
#include "slus/imports.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/effect/motion.h"

void retire_finished_sprite_effect(void *body, ObjectPosition *position, SpriteFrameState *sprite)
{
    advance_sprite_animation_and_textures(sprite);
    if (sprite->flags & 0x6000) {
        NODE_HEADER(body)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
