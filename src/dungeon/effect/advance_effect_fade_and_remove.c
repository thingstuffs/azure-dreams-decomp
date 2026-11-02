#include "common.h"
#include "shared/sprite_source.h"
#include "dungeon/effect.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect/motion/variant_effect_with_random_motion.h"
#include "slus.h"

struct Dst;
struct Elem;

typedef struct S_800B7C14_1_pre {
    u16 unk_00;
} S_800B7C14_1_pre;   /* the 0x2 bytes before arg0 in advance_effect_fade_and_remove, addressed as arg0[-1] */

/* Advance effect motion, fade its primitive, and mark it for removal when its lifetime ends. */
void advance_effect_fade_and_remove(VariantEffectWithRandomMotionBody *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
    s32 velocity_x;
    u16 life_left;
    u8 brightness;

    if (primitive->unk_00 != 0) {
        advance_sprite_animation_and_textures(primitive);
        if (primitive->flags & 0x4000) {
            select_record_entry_and_value(primitive, effect->sprite_entries, 0);
        }
    }
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    velocity_x = motion->velocity_x;
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    motion->velocity_x = (s32) (velocity_x - (velocity_x >> 4));
    motion->velocity_y = (s32) (motion->velocity_y - (motion->velocity_y
        >> 4));
    motion->velocity_z = (s32) (motion->velocity_z + 0x40000);
    if (effect->fade_color != 0) {
        brightness = primitive->color.c.r;
        if (brightness != 0) {
            brightness -= 8;
            primitive->color.c.r = brightness;
            primitive->color.c.b = brightness;
            primitive->color.c.g = brightness;
        }
    }
    primitive->angle_x = (u16) (primitive->angle_x
        + effect->angle_x_step.u);
    primitive->angle_y = (u16) (primitive->angle_y
        + effect->angle_y_step.u);
    life_left = effect->lifetime.u - 1;
    effect->lifetime.u = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B7C14_1_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
