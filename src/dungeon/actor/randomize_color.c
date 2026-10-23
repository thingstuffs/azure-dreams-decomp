#include "common.h"
#include "shared/sprite_frame_state.h"

typedef struct { u8 pad[0xE]; u16 flags; } SpriteOwner;
typedef struct { u16 flags; u16 unused; SpriteOwner *owner; } OwnerLink;
typedef struct { u8 pad[0xC]; u8 r, g, b; u8 padF[5]; u16 flags; } Render;
typedef struct { s32 flags; } GlobalFlags;
extern GlobalFlags object_flag_block;
extern void advance_sprite_animation_and_textures(Render *);
extern s32 rand(void);

/* Randomize color and mark the owner complete when the render flags request it. */
void randomize_color(SpriteOwner **action, void *unused, SpriteFrameState *render) {
    (*action)->flags |= 0x8000;
    advance_sprite_animation_and_textures(render);
    render->color.c.r = (rand() & 0x7F) + 0x20;
    render->color.c.g = (rand() & 0x7F) + 0x20;
    render->color.c.b = (rand() & 0x7F) + 0x20;
    if (render->flags & 0x6000) {
        GlobalFlags *status = &object_flag_block;
        ((OwnerLink *)((u8 *)action - 4))->unused |= 0x8000;
        status->flags |= 0x8000;
    }
}
