#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"


   /* the 0x2 bytes before arg0 in update_fading_effect_motion, addressed as arg0[-1] */

typedef struct S_800A86BC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    s32 unk_04;
} S_800A86BC_1;   /* arg0 in update_fading_effect_motion */

extern void advance_sprite_animation_and_textures();

/* Update effect motion, fade its primitive, and flag expiration when its timer ends. */
void update_fading_effect_motion(void *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
    u8 shade;
    u16 ticks_left;

    motion->velocity_z = motion->velocity_z + ((S_800A86BC_1 *)effect)->unk_04;
    motion->x.v = motion->x.v + motion->velocity_x;
    motion->y.v = motion->y.v + motion->velocity_y;
    motion->z.v = motion->z.v + motion->velocity_z;
    advance_sprite_animation_and_textures(primitive);
    shade = primitive->color.c.r;
    if (shade != 0) {
        shade -= 0x10;
        primitive->color.c.r = shade;
        primitive->color.c.b = shade;
        primitive->color.c.g = shade;
    }
    ticks_left = ((S_800A86BC_1 *)effect)->unk_02 - 1;
    ((S_800A86BC_1 *)effect)->unk_02 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].flags = ((ObjectRetirementFlags *)effect)[-1].flags | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
