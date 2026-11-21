#include "dungeon/effect/attached_sprite_burst.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/object_node_flags.h"
#include "slus/imports.h"

/* The selector-52 burst installs this callback and links each child to its action. */
void update_drifting_effect(DriftingEffect *effect, ObjectPosition *motion, SpriteFrameState *render) {
    motion->z.v += motion->velocity_z;
    effect->parent->flags |= 0x8000;
    advance_sprite_animation_and_textures(render);
    if (render->flags & 0x6000) {
        ObjectFlagBlock *status = &object_flag_block;
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        status->flags |= OBJECT_REMOVE_PENDING;
    }
}
