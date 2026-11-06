#include "shared/sprite_frame_state.h"
#include "common.h"
#include "slus/imports.h"
#include "shared/object_flags.h"

typedef struct {
    u32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} VecState;

typedef struct {
    u8 pad[0x48];
    u16 timer;
} EffectState;


/* Advance effect motion, update its data, and set expiry flags when its timer runs out. */
void update_linear_motion_effect(EffectState *effect, VecState *motion, SpriteFrameState *update_data) {
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;
    advance_sprite_animation_and_textures(update_data);
    if ((s16)--effect->timer <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
