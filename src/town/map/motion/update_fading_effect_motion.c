#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_links.h"
#include "slus.h"
#include "town/map/motion.h"


   /* the 0x2 bytes before arg0 in update_fading_effect_motion, addressed as arg0[-1] */



/* Update effect motion, fade its primitive, and flag expiration when its timer ends. */
void update_fading_effect_motion(FadingEffectMotionObject *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
    u8 shade;
    u16 ticks_left;

    motion->velocity_z = motion->velocity_z + effect->velocity_z_acceleration;
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
    ticks_left = effect->timer.remaining_ticks - 1;
    effect->timer.remaining_ticks = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].flags = ((ObjectRetirementFlags *)effect)[-1].flags | 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
