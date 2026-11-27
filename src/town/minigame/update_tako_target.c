#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/minigame/effect.h"
#include "town/scene/object.h"
#include "town/data.h"
#include "town/minigame.h"
#include "town/minigame/tako_child_body.h"

extern u8 tako_minigame_sprites[16];
extern u8 D_800F79E8[16];


/* Updates entity animation, vertical motion, particles, and timed removal. */
void update_tako_target(TakoChildBody *entity, ObjectPosition *motion, SpriteFrameState *sprite) {
    TakoMinigameState *cell = entity->parent;
    s32 cell_flags;
    s32 state;
    s32 particles_left;
    s32 random_value;
    s32 particle_x;

    if (entity->flags & 2) {
        if (sprite->color.c.r) {
            sprite->color.word += 0xfffefeff;
        }
    }

    cell_flags = cell->flags;
    cell->flags = cell_flags | 2;
    if (entity->flags & 1) {
        cell->flags = cell_flags | 6;
    }

    advance_sprite_animation_and_textures(sprite);
    if (entity->flags & 4) {
        if (sprite->frame_entry == (void *)tako_minigame_sprites) {
            select_record_entry_and_value(sprite, D_800F79E8, 0);
        }
    }
    if (sprite->flags & 0x6000) {
        select_record_entry_and_value(sprite, tako_minigame_sprites, 0);
    }

    state = entity->state;
    switch (state) {

    case 0:
        if (motion->z.v > 0) {
            motion->z.v += motion->velocity_z;
            for (particles_left = 3; particles_left >= 0; particles_left--) {
                random_value = rand();
                particle_x = motion->x.v;
                particle_x += ((random_value & 0xff) - 128) << 14;
                random_value = rand();
                create_tinted_animated_particle(0x808080, particle_x, motion->y.v + 0x80000, (random_value & 0xf) << 16);
            }
            break;
        }
        motion->z.v = 0;
        motion->velocity_z = 0;
        entity->state = 1;
        break;

    case 1:
        if (cell->flags & 1) {
            TakoProjectileBody effect;
            u8 *effect_entry = tako_target_timing_table + cell->table_y * 400 + cell->table_x * 40 + (entity->column_index * 12 + 4);
            effect.timer = *(u16 *)(effect_entry + 8);
            effect.velocity_x = *(s32 *)(effect_entry + 0);
            effect.acceleration_x = *(s32 *)(effect_entry + 4);
            effect.phase = 0;
            effect.flags = 0;
            effect.target = entity;
            create_tako_projectile(&effect, motion->y.v, 0);
        }
        break;

    case 2:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            if (entity->column_index == 0) {
                create_timed_sound(90);
            }
            motion->velocity_z = 0x40000;
            entity->state = 3;
        }
    }
        break;

    case 3:
        if (motion->z.v <= 0x7fffff) {
            {
                s32 height = motion->z.v + motion->velocity_z;
                motion->z.v = height;
                if (height <= 0x3fffff) {
                    for (particles_left = 3; particles_left >= 0; particles_left--) {
                        random_value = rand();
                        particle_x = random_value & 0xff;
                        particle_x -= 128;
                        particle_x <<= 14;
                        particle_x += 0x5600000;
                        random_value = rand();
                        create_tinted_animated_particle(0x808080, particle_x, motion->y.v + 0x80000, (random_value & 0xf) << 16);
                    }
                }
            }
            break;
        }
        entity->timer = 2;
        entity->state = 4;
        break;

    case 4:
    {
        s32 timer_left = entity->timer - 1;
        entity->timer = timer_left;
        if ((s16)timer_left <= 0) {
            unlink_scene_list_node((u8 *)entity + 4);
            ((ObjectNodeHeader *)entity - 1)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }

    }
    entity->flags &= ~2;
}
