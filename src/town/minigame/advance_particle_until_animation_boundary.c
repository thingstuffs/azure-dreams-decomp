#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} S_8081C8DC;

extern void advance_sprite_animation_and_textures(void *result);

/* Advances the position and propagates flags from the processed result. */
void advance_particle_until_animation_boundary(void *object_data, S_8081C8DC *motion, S_8081C8DC *result)
{
    s32 delta_y;
    s32 delta_z;

    delta_y = motion->field10;
    delta_z = motion->field14;
    motion->field0 += motion->fieldC;
    motion->field4 += delta_y;
    motion->field8 += delta_z;
    advance_sprite_animation_and_textures(result);
    if (*(u16 *)((u8 *)result + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_data - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
