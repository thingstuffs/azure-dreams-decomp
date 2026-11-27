#include "common.h"
#include "dungeon/level.h"
#include "shared/dungeon_height_query.h"
#include "dungeon/monster/blume.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct { u16 flags; } EffectFieldView_80DB9C2CPrefix;



/* Update effect motion, collisions, sprite growth, and timed fading. */
void update_growing_colliding_effect(GrowingCollidingEffectBody *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    s32 move_height;
    s32 fade_height;
    s32 phase;
    s32 fade_level;
    s32 velocity_x;
    s32 velocity_y;
    u16 anim_tick;
    u16 move_scale_x;
    u16 move_scale_y;
    u16 move_ticks_left;
    u16 fade_scale_x;
    u16 fade_scale_y;
    u16 fade_ticks_left;

    if (effect->phase == 0) {
        position->x.v += effect->velocity_x;
        velocity_x = effect->velocity_x;
        effect->velocity_x = (velocity_x * 2) / 3;
        if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            position->z.w.i) << 0x10) != 0) {
            position->x.v -= effect->velocity_x;
            effect->velocity_x = 0;
            effect->unk_6C = 0;
        }
        position->y.v += effect->velocity_y;
        velocity_y = effect->velocity_y;
        effect->velocity_y = (velocity_y * 2) / 3;
        if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            position->z.w.i) << 0x10) != 0) {
            position->y.v -= effect->velocity_y;
            effect->velocity_y = 0;
            effect->unk_70 = 0;
        }
        position->z.v += effect->velocity_z;
        effect->velocity_z += effect->acceleration_z;
        move_height = position->z.w.i;
        if (((s16)sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)((u16)position->z.w.i - 4)) - 0x10) < move_height) {
            effect->velocity_z = 0;
            position->z.w.i = (s16)sample_terrain_surface_height(position->x.unsigned_parts.integer,
                position->y.unsigned_parts.integer, (s16)((u16)position->z.w.i - 4))
            - 0x11;
            position->z.w.frac = 0;
            if (effect->phase_latch == 0) {
                effect->phase_latch = 1;
                effect->ticks_left = 0;
            }
        }
        anim_tick = effect->tick_count + 1;
        effect->tick_count = anim_tick;
        if (!(anim_tick & 3)) {
            advance_sprite_animation_and_textures(sprite);
        }
        move_scale_x = sprite->scale_x + 0x64;
        sprite->scale_x = move_scale_x;
        if ((u32)(move_scale_x & 0xFFFF) >= 0x2001U) {
            sprite->scale_x = 0x2000;
        }
        move_scale_y = sprite->scale_y + 0x64;
        sprite->scale_y = move_scale_y;
        if ((u32)(move_scale_y & 0xFFFF) >= 0x2001U) {
            sprite->scale_y = 0x2000;
        }
        move_ticks_left = effect->ticks_left - 1;
        effect->ticks_left = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            effect->phase_latch = 0;
            effect->phase = (u16)effect->phase + 1;
        }
        if (sprite->flags & 0x8000) {
            (((EffectFieldView_80DB9C2CPrefix *)effect)[-1].flags) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    phase = effect->phase;
    if (phase == 1) {
        if (effect->phase_latch == 0) {
            effect->phase_latch = phase;
            effect->ticks_left = 0x14;
            effect->tick_count = 0x14;
            effect->velocity_y = 0;
            effect->velocity_x = 0;
        }
        fade_scale_x = sprite->scale_x + 0xC8;
        sprite->scale_x = fade_scale_x;
        if ((u32)(fade_scale_x & 0xFFFF) >= 0x2001U) {
            sprite->scale_x = 0x2000;
        }
        fade_scale_y = sprite->scale_y + 0xC8;
        sprite->scale_y = fade_scale_y;
        if ((u32)(fade_scale_y & 0xFFFF) >= 0x2001U) {
            sprite->scale_y = 0x2000;
        }
        position->z.v += effect->velocity_z;
        effect->velocity_z += effect->acceleration_z;
        fade_height = position->z.w.i;
        if (((s16)sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)((u16)position->z.w.i - 4)) - 0x10) < fade_height) {
            effect->velocity_z = 0;
            position->z.w.i = (s16)sample_terrain_surface_height(position->x.unsigned_parts.integer,
                position->y.unsigned_parts.integer, (s16)((u16)position->z.w.i - 4))
            - 0x11;
            position->z.w.frac = 0;
            if (effect->phase_latch == 0) {
                effect->phase_latch = phase;
                effect->ticks_left = 0;
            }
        }
        fade_level = ((s16)effect->ticks_left << 7) / (s16)effect->tick_count;
        sprite->color.c.b = 0;
        sprite->color.c.g = fade_level;
        sprite->color.c.r = fade_level;
        fade_ticks_left = effect->ticks_left - 1;
        effect->ticks_left = fade_ticks_left;
        if ((fade_ticks_left << 0x10) <= 0) {
            (((EffectFieldView_80DB9C2CPrefix *)effect)[-1].flags) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
