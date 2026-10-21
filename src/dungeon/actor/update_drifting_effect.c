#include "common.h"

typedef struct { u8 pad[0x52]; u16 flags; } SpriteOwner;
typedef struct { u8 pad[8]; s32 position; u8 padC[8]; s32 velocity; } Motion;
typedef struct { u8 pad[0x14]; u16 flags; } Render;
typedef struct { s32 flags; } GlobalFlags;
extern GlobalFlags D_800814A0;
extern void advance_sprite_animation_and_textures(Render *);

/* Advance effect motion and mark its owner when drawing has completed. */
void update_drifting_effect(SpriteOwner **action, Motion *motion, Render *render) {
    motion->position += motion->velocity;
    (*action)->flags |= 0x8000;
    advance_sprite_animation_and_textures(render);
    if (render->flags & 0x6000) {
        GlobalFlags *status = &D_800814A0;
        ((u16 *)action)[-1] |= 0x8000;
        status->flags |= 0x8000;
    }
}
