#include "common.h"
#include "slus/imports.h"
#include "dungeon/monster/baloon.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_node.h"

   /* the 0x2 bytes before arg0 in update_effect_collision_and_lifetime, addressed as arg0[-1] */

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Updates effect motion, terrain collisions, visual properties, and lifetime. */
void update_effect_collision_and_lifetime(OriginMotionEffectBody *effect, ObjectPosition *position, SpriteFrameState *visual)
{
    s16 life_left;
    s32 current_z;
    s32 life_scale;
    s32 terrain_z;
    u16 updated_value;
    u16 x;
    u16 z;

    position->z.v += effect->velocity_z;
    effect->velocity_z += effect->acceleration_z;

    x = position->x.unsigned_parts.integer;
    z = position->z.unsigned_parts.integer;
    current_z = position->z.w.i;
    terrain_z = sample_terrain_surface_height(x,
                              position->y.unsigned_parts.integer,
                              (s16)(z - 4));
    if (terrain_z - 0x10 < current_z) {
        effect->velocity_z = 0;
        position->z.w.i =
            sample_terrain_surface_height(position->x.unsigned_parts.integer,
                          position->y.unsigned_parts.integer,
                          (s16)(position->z.unsigned_parts.integer - 4)) - 0x11;
        position->z.w.frac = 0;
        if (effect->state == 0) {
            effect->state = 1;
        }
    }

    if (effect->state == 1) {
        position->x.v += effect->velocity_x;
        effect->velocity_x += effect->acceleration_x;
        if (sample_terrain_surface_height(position->x.unsigned_parts.integer,
                          position->y.unsigned_parts.integer,
                          position->z.w.i) < 0x200 &&
            (s16)check_left_tile_and_center_height(position->x.unsigned_parts.integer,
                               position->y.unsigned_parts.integer,
                               position->z.w.i) != 0) {
            position->x.v -= effect->velocity_x;
            effect->velocity_x = 0;
            effect->acceleration_x = 0;
        }

        position->y.v += effect->velocity_y;
        effect->velocity_y += effect->acceleration_y;
        if (sample_terrain_surface_height(position->x.unsigned_parts.integer,
                          position->y.unsigned_parts.integer,
                          position->z.w.i) < 0x200 &&
            (s16)check_left_tile_and_center_height(position->x.unsigned_parts.integer,
                               position->y.unsigned_parts.integer,
                               position->z.w.i) != 0) {
            position->y.v -= effect->velocity_y;
            effect->velocity_y = 0;
            effect->acceleration_y = 0;
        }
    }

    life_scale = (effect->lifetime.s << 7) / effect->lifetime_divisor;
    visual->color.c.b = life_scale;
    visual->color.c.g = life_scale;
    visual->color.c.r = life_scale;

    updated_value = effect->animation_counter + 1;
    effect->animation_counter = updated_value;
    if ((s16)updated_value == 3) {
        advance_sprite_animation_and_textures(visual);
        effect->animation_counter = 0;
    }

    updated_value = visual->scale_x + 0xC8;
    visual->scale_x = updated_value;
    if (updated_value > 0x1000) {
        visual->scale_x = 0x1000;
    }

    updated_value = visual->scale_y + 0xC8;
    visual->scale_y = updated_value;
    if (updated_value > 0x1000) {
        visual->scale_y = 0x1000;
    }

    life_left = effect->lifetime.u - 1;
    effect->lifetime.u = life_left;
    if ((life_left << 16) <= 0) {
        NODE_HEADER(effect)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
