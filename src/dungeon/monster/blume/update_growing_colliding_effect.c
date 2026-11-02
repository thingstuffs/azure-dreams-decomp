#include "common.h"
#include "dungeon/monster/blume.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct { u16 flags; } EffectFieldView_80DB9C2CPrefix;


extern s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height();

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

    if (effect->unk_00 == 0) {
        position->x.v += effect->unk_60;
        velocity_x = effect->unk_60;
        effect->unk_60 = (velocity_x * 2) / 3;
        if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            position->z.w.i) << 0x10) != 0) {
            position->x.v -= effect->unk_60;
            effect->unk_60 = 0;
            effect->unk_6C = 0;
        }
        position->y.v += effect->unk_64;
        velocity_y = effect->unk_64;
        effect->unk_64 = (velocity_y * 2) / 3;
        if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            position->z.w.i) << 0x10) != 0) {
            position->y.v -= effect->unk_64;
            effect->unk_64 = 0;
            effect->unk_70 = 0;
        }
        position->z.v += effect->unk_68;
        effect->unk_68 += effect->unk_74;
        move_height = position->z.w.i;
        if ((sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)((u16)position->z.w.i - 4)) - 0x10) < move_height) {
            effect->unk_68 = 0;
            position->z.w.i = sample_terrain_surface_height(position->x.unsigned_parts.integer,
                position->y.unsigned_parts.integer, (s16)((u16)position->z.w.i - 4))
            - 0x11;
            position->z.w.frac = 0;
            if (effect->unk_1A == 0) {
                effect->unk_1A = 1;
                effect->unk_24 = 0;
            }
        }
        anim_tick = effect->unk_26 + 1;
        effect->unk_26 = anim_tick;
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
        move_ticks_left = effect->unk_24 - 1;
        effect->unk_24 = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            effect->unk_1A = 0;
            effect->unk_00 = (u16)effect->unk_00 + 1;
        }
        if (sprite->flags & 0x8000) {
            (((EffectFieldView_80DB9C2CPrefix *)effect)[-1].flags) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    phase = effect->unk_00;
    if (phase == 1) {
        if (effect->unk_1A == 0) {
            effect->unk_1A = phase;
            effect->unk_24 = 0x14;
            effect->unk_26 = 0x14;
            effect->unk_64 = 0;
            effect->unk_60 = 0;
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
        position->z.v += effect->unk_68;
        effect->unk_68 += effect->unk_74;
        fade_height = position->z.w.i;
        if ((sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)((u16)position->z.w.i - 4)) - 0x10) < fade_height) {
            effect->unk_68 = 0;
            position->z.w.i = sample_terrain_surface_height(position->x.unsigned_parts.integer,
                position->y.unsigned_parts.integer, (s16)((u16)position->z.w.i - 4))
            - 0x11;
            position->z.w.frac = 0;
            if (effect->unk_1A == 0) {
                effect->unk_1A = phase;
                effect->unk_24 = 0;
            }
        }
        fade_level = ((s16)effect->unk_24 << 7) / (s16)effect->unk_26;
        sprite->color.c.b = 0;
        sprite->color.c.g = fade_level;
        sprite->color.c.r = fade_level;
        fade_ticks_left = effect->unk_24 - 1;
        effect->unk_24 = fade_ticks_left;
        if ((fade_ticks_left << 0x10) <= 0) {
            (((EffectFieldView_80DB9C2CPrefix *)effect)[-1].flags) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
