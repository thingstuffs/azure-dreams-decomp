#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *work);

/* Advances object motion, decrements its timer, and flags expiration. */
void tick_object_motion_and_expire(void *object_data, void *motion_data, void *work_data)
{
    s32 *motion = motion_data;
    u8 *object = object_data;
    SpriteFrameState *work= work_data;
    s16 timer;

    work->color.word -= *(s32 *)(object + 0xA4);
    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];

    timer = *(u16 *)(object + 0x96) - 1;
    *(u16 *)(object + 0x96) = timer;
    if (timer <= 0) {
        *(u16 *)(object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    advance_sprite_animation_and_textures(work);
}
