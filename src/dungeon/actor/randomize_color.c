#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "common.h"
#include "slus/imports.h"
#include "shared/sprite_frame_state.h"
#include "sdk/libc.h"

typedef struct { u8 pad[0xE]; u16 flags; } SpriteOwner;

/* Randomize color and mark the owner complete when the render flags request it. */
void randomize_color(SpriteOwner **action, ObjectPosition *unused, SpriteFrameState *render) {
    (*action)->flags |= 0x8000;
    advance_sprite_animation_and_textures(render);
    render->color.c.r = (rand() & 0x7F) + 0x20;
    render->color.c.g = (rand() & 0x7F) + 0x20;
    render->color.c.b = (rand() & 0x7F) + 0x20;
    if (render->flags & 0x6000) {
        ObjectFlagBlock *status = &object_flag_block;
        NODE_HEADER(action)->flags |= 0x8000;
        status->flags |= OBJECT_REMOVE_PENDING;
    }
}
