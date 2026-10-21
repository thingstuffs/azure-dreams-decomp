#include "common.h"
#include "shared/object_flags.h"

extern void advance_sprite_animation_and_textures(void *);
extern s32 func_800644B8(s16);
extern s32 func_80064584(s16);

/* Updates radial position or sets completion flags based on the object state. */
void update_radial_motion_or_complete(u16 *motion, s32 *position, u8 *object)
{
    s32 y_offset;

    motion[0]++;
    advance_sprite_animation_and_textures(object);
    if (*(u16 *)(object + 0x14) & 0x6000) {
        motion[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    motion[3] += motion[4];
    position[0] = position[3] + (((func_80064584((s16)motion[2]) >> 4) *
                           (s16)motion[3]) << 8);
    y_offset = (func_800644B8((s16)motion[2]) >> 4) * (s16)motion[3];
    *(u16 *)((u8 *)position + 0xA) -= 2;
    position[1] = position[4] + (y_offset << 8);
}
