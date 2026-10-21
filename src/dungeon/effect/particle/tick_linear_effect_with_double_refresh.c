#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Position;

extern void advance_sprite_animation_and_textures();

/* Advance the position and timer, setting completion flags when the timer expires. */
void tick_linear_effect_with_double_refresh(void *state, Position *pos, s32 handle)
{
    s32 dy;
    s32 dz;
    u16 timer;

    dy = pos->dy;
    dz = pos->dz;
    pos->x += pos->dx;
    pos->y += dy;
    pos->z += dz;
    advance_sprite_animation_and_textures(handle);
    advance_sprite_animation_and_textures(handle);
    timer = *(u16 *)((u8 *)state + 0x32) - 1;
    *(u16 *)((u8 *)state + 0x32) = timer;
    if ((timer << 16) <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
