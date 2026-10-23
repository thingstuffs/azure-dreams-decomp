#include "shared/audio_commands.h"
/* Expanding moving sprites and staged attachment, particle emission, and cleanup effects. */
#include "dungeon/effect/particle/interpolate_view_parameters.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

void (*const dungeon_18e8800_entry)(B31_818C8FD0_S_func_818C8FD0_1 *, B31_818C8FD0_S_func_818C8FD0_4 *, B31_818C8FD0_S_func_818C8FD0_5 *) = update_an_effect_through_attachment_motion_timed_cleanup;
const B31_818C8FD0_OffsetTable D_80024004 = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};

   /* the 0x2 bytes before arg0 in interpolate_view_parameters, addressed as arg0[-1] */

/* Apply the effect offset, update its object, and flag expired or inactive effects. */
extern u8 directional_sprite_entries[];
extern u8 current_spell_effect_variant;
extern u8 directional_sprite_entries[];

/* Moves and animates an expanding sprite, removing it when its lifetime ends or its hidden flag is set. */
void interpolate_view_parameters(B31_818C8824_EffectState *state, s32 *position, B31_818C8824_EffectObject *object)
{
    u16 life;

    position[0] += state->x;
    position[1] += state->y;
    moving_particle_effect_updated = 1;
    position[2] += state->z;
    advance_sprite_animation_and_textures(object);
    object->field1C += 0x80;
    object->field1E += 0x80;
    life = state->life - 1;
    state->life = life;
    if ((life << 16) <= 0) {
        ((B31_818C8824_S_818C8824_0_pre *)state)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        ((B31_818C8824_S_818C8824_0_pre *)state)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* the 0x2 bytes before arg0 in func_80024124, addressed as arg0[-1] */

/* Advance effect motion and lifetime, updating its object and marking completion. */
void advance_accelerating_particle(B31_818C8924_EffectState *effect, s32 *position, B31_818C8924_EffectObject *object)
{
    u16 timer;
    u16 life;

    effect->x += effect->vx;
    effect->y += effect->vy;
    effect->z += effect->vz;
    position[0] += effect->x;
    position[1] += effect->y;
    position[2] += effect->z;

    moving_particle_effect_updated = 1;
    timer = effect->timer + 1;
    effect->timer = timer;
    if (!(timer & 1)) {
        advance_sprite_animation_and_textures(object);
    }

    object->field1C += 200;
    object->field1E += 200;

    life = effect->life - 1;
    effect->life = life;
    if ((life << 16) <= 0) {
        ((B31_818C8924_S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        ((B31_818C8924_S_818C8924_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* the 0x2 bytes before arg0 in update_a_moving_effect_spawns_particles_advances_timed_phases, addressed as arg0[-1] */

   /* arg0 in update_a_moving_effect_spawns_particles_advances_timed_phases */

   /* arg1 in update_a_moving_effect_spawns_particles_advances_timed_phases */

   /* the 0x18 bytes before ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30 in update_a_moving_effect_spawns_particles_advances_timed_phases, addressed as ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30[-1] */

/* cfail-repair: tf7-phase1-cache-v3 */

/* Updates a moving effect, spawns particles, and advances its timed phases. */
void update_a_moving_effect_spawns_particles_advances_timed_phases(void *effect, B31_818C8A70_S_818C8A70_4 *position) {
    s32 effect_mode;
    s16 coord;
    s16 coord_2;
    s16 phase;
    s32 effect_value;
    u8 random_value;
    u16 remaining_ticks;
    u16 burst_ticks;
    u16 fade_ticks;
    B31_818C8A70_S_818C8A70_3 *sprite;
    ObjectPosition *particle_pos;
    B31_818C8A70_S_818C8A70_1 *particle_state;   /* retained from the base: holds the repeated particle-state role */
    B31_818C8A70_S_818C8A70_6 *source;
    ObjectNodeHeader *particle;

    moving_particle_effect_updated = 1;
    source = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_2C;
    if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 == 0) {
        particle = allocate_flagged_object_node(0x212);
        particle_state = ((void *)particle) + 0x20;
        if (particle != NULL) {
            particle_state->unk_02 = 0x1A;
            particle->unk_10 = advance_accelerating_particle;
            register_node(particle, project_sprite_chain);
            sprite = particle->sprite;
            sprite->unk_10 = 0x60;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
            particle_pos = particle->position;
            random_value = rand();
            coord = position->unk_00.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->x.w.i = coord;
            random_value = rand();
            coord = position->unk_04.at02.v;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->y.w.i = coord;
            random_value = rand();
            coord = position->unk_08.at02.v;
            coord -= 4;
            coord += random_value & 7;
            particle_pos->z.w.i = coord;
            particle_state->unk_60 = (s32) (rand() + 0xFFFE0000);
            sprite = particle->sprite;
            sprite->unk_1C = 0x1000;
            sprite->unk_1E = 0x1000;
            sprite->unk_0E = 0x80;
            sprite->unk_0D = 0x80;
            sprite->unk_0C = 0x80;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
            select_record_entry_and_value(sprite, effect_sprite_sources, 0);
        }
        remaining_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 - 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_08 != 0) {
                ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 = 1;
                ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = 0U;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            } else {
                ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
                object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            }
        }
        if ((check_adjacent_tile_height_clearance(position->unk_00.at02.v, position->unk_04.at02.v, (s16) position->unk_08.at02.v, ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30) << 0x10) == 0) {
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_58);
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_5C);
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_60);
        } else {
            ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            return;
        }
    }
    phase = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00;
    if (phase == 1) {
        burst_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 + 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = burst_ticks;
        if ((burst_ticks & 3) == phase) {
            particle = allocate_flagged_object_node(0x212);
            particle_state = ((void *)particle) + 0x20;
            if (particle != NULL) {
                u32 particle_z;
                u16 particle_z_base;
                particle_state->unk_02 = 0x1A;
                particle->unk_10 = advance_accelerating_particle;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                sprite->unk_10 = 0x60;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = particle->position;
                sprite = ((B31_818C8A70_S_818C8A70_7_pre *)(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = rand();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->x.w.i = coord;
                random_value = rand();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->y.w.i = coord;
                random_value = rand();
                random_value &= 0x1F;
                particle_z_base = sprite->unk_0A;
                random_value += 0x10;
                particle_z = (u32)particle_z_base - random_value;
                particle_pos->z.w.i = particle_z;
                particle_state->unk_58 = (s32) (rand() - 0x8000);
                particle_state->unk_5C = (s32) (rand() - 0x8000);
                particle_state->unk_60 = (s32) ((rand() + 0xFFFC0000) * 2);
                sprite = particle->sprite;
                sprite->unk_1C = 0x1000;
                sprite->unk_1E = 0x1000;
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DCF;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                select_record_entry_and_value(sprite, effect_sprite_sources, 0);
            }
        }
        if ((((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 & 3) == 2) {
            particle = allocate_flagged_object_node(0x212);
            particle_state = ((void *)particle) + 0x20;
            if (particle != NULL) {
                s16 particle_z;
                particle_state->unk_02 = 0x14;
                particle->unk_10 = interpolate_view_parameters;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                sprite->unk_10 = 0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
                particle_pos = particle->position;
                sprite = ((B31_818C8A70_S_818C8A70_7_pre *)(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30))[-1].unk_00;
                random_value = rand();
                coord = sprite->unk_02;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->x.w.i = coord;
                random_value = rand();
                coord = sprite->unk_06;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->y.w.i = coord;
                random_value = rand();
                random_value &= 0x3F;
                coord_2 = sprite->unk_0A;
                random_value += 0x20;
                particle_z = coord_2 - random_value;
                particle_pos->z.w.i = particle_z;
                sprite = particle->sprite;
                sprite->unk_1C = 0x800;
                sprite->unk_1E = 0x800;
                particle_state->unk_60 = (s32) (rand() + 0xFFFE0000);
                sprite->unk_0E = 0x80;
                sprite->unk_0D = 0x80;
                sprite->unk_0C = 0x80;
                sprite->unk_12 = 0x7DC0;
                sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
                select_record_entry_and_value(sprite, directional_sprite_entries, 0);
            }
        }
        if ((s16) ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 >= 0x29) {
            ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 = 2;
            ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = 0U;
            if (try_trigger_target_record_effect(source->unk_60, 1, source) == 0) {
                s16 random_bonus;
                u32 effect_scale;
                random_bonus = generate_random_value();
                random_bonus &= 3;
                effect_scale = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_15;
                random_bonus += 2;
                effect_scale >>= 2;
                effect_value = effect_scale + random_bonus;
                effect_mode = 0x10;
                if (current_spell_effect_variant == 0xFF) {
                    effect_mode = 0xFF;
                }
                try_apply_confusion_status(((B31_818C8A70_S_818C8A70_0 *)effect)->unk_30, effect_mode, effect_value);
            }
        }
    }
    if (((B31_818C8A70_S_818C8A70_0 *)effect)->unk_00 == 2) {
        fade_ticks = ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 + 1;
        ((B31_818C8A70_S_818C8A70_0 *)effect)->unk_02 = fade_ticks;
        if ((s16) fade_ticks >= 0x15) {
            ((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 = (u16) (((B31_818C8A70_S_818C8A70_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        }
    }
}

/* Updates an effect through attachment, motion, and timed cleanup. */
void update_an_effect_through_attachment_motion_timed_cleanup(B31_818C8FD0_S_func_818C8FD0_1 *state, B31_818C8FD0_S_func_818C8FD0_4 *output_pos, B31_818C8FD0_S_func_818C8FD0_5 *part)
{
    s16 delta[3];
    s32 mode;
    u16 angle;
    u16 frame_count;
    B31_818C8FD0_OffsetTable offsets;
    B31_818C8FD0_S_func_818C8FD0_2 *object;
    B31_818C8FD0_S_func_818C8FD0_3 *owner_node;
    B31_818C8FD0_S_func_818C8FD0_4 *owner_pos;
    ObjectNodeHeader *effect_node;
    ObjectPosition *effect_pos;
    B31_818C8FD0_OffsetTable *offset_table;
    s32 one;
    B31_818C8FD0_OffsetTable *offset_source = &D_80024004;

    object = state->unk_00;
    offsets = *offset_source;
    offset_table = &offsets;
    one = 1;
    frame_count = state->unk_82;
    mode = state->unk_0A.s16;
    owner_node = (B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object - 0x20);
    owner_pos = owner_node->unk_08;
    frame_count++;
    state->unk_82 = frame_count;

    switch (mode) {
    case 0:
        part->unk_0C = 0x00808080;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        select_record_entry_and_value(part, directional_sprite_entries, 0);
        angle = object->unk_2A;
        moving_particle_effect_updated = one;
        state->unk_7E.s16 = (angle >> 9) & 7;
        state->unk_0A.u16++;
    case 1:
        {
            B31_818C8FD0_S_func_818C8FD0_6 *owner_part;
            u16 position_z;
            u16 final_z;
            u16 delta_z;

            owner_part = owner_node->unk_0C;

            if ((get_sprite_attachment_vector(owner_part->unk_08, owner_part, delta, 0) != 0) ||
                (((B31_818C8FD0_S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
                output_pos->unk_00.u16.unk_02 = owner_pos->unk_00.u16.unk_02;
                output_pos->unk_04.u16.unk_06 = owner_pos->unk_04.u16.unk_06;
                position_z = owner_pos->unk_08.u16.unk_0A;
                output_pos->unk_08.u16.unk_0A = position_z;

                if (!(((B31_818C8FD0_S_func_818C8FD0_6 *)owner_node->unk_0C)->unk_14 & 0x8000)) {
                    output_pos->unk_00.u16.unk_02 += (u16)delta[0];
                    output_pos->unk_04.u16.unk_06 += (u16)delta[1];
                    final_z = output_pos->unk_08.u16.unk_0A;
                    delta_z = (u16)delta[2];
                    final_z += delta_z;
                    output_pos->unk_08.u16.unk_0A = final_z;
                } else {
                    final_z = position_z - 0x40;
                    output_pos->unk_08.u16.unk_0A = final_z;
                }

                if (((B31_818C8FD0_S_func_818C8FD0_10 *)state->unk_04)->unk_00 & 0x80) {
                    state->unk_84.s16 = 0;
                    state->unk_0A.u16++;
                    return;
                }
            }
            return;
        }
    case 2:
        {

            effect_node = allocate_flagged_object_node(0x12);

            if (effect_node != 0) {
                B31_818C8FD0_S_func_818C8FD0_7 *effect;
                s32 direction_index;
                B31_818C8FD0_S_func_818C8FD0_8 *tile;

                effect = (B31_818C8FD0_S_func_818C8FD0_7 *)((u8 *)effect_node + 0x20);

                {
                    s16 *direction_offset;

                    direction_index = state->unk_7E.s16;
                    direction_offset = (s16 *)((u8 *)offset_table + direction_index * 4);
                    effect->unk_58 = (s32)direction_offset[0] << 16;
                }
                {
                    u16 *direction_offset;

                    direction_index = state->unk_7E.s16;
                    direction_offset = (u16 *)((u8 *)offset_table + direction_index * 4);
                    effect->unk_5C = (s32)direction_offset[1] << 16;
                }
                effect->unk_2C = object;
                effect->unk_30 = object->unk_60.s32;
                effect->unk_0A = (state->unk_84.s16 - 1) / 2;
                effect->unk_15 = state->unk_09;
                effect->unk_16 = state->unk_7E.u16;

                {
                    u8 *table_base = (u8 *)((s8 *)dir_step_x);

                    direction_index = state->unk_7E.s16 * 2;
                    tile = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object - 0x20))->unk_0C;
                    state->unk_A0 =
                        tile->unk_24 + table_base[direction_index];
                }
                {
                    u8 *table_base = (u8 *)((s8 *)dir_step_y);

                    direction_index = state->unk_7E.s16 * 2;
                    state->unk_A1 =
                        tile->unk_25 + table_base[direction_index];
                }

                if (object->unk_60.ptr != 0) {
                    s32 tile_distance;
                    s32 duration;
                    B31_818C8FD0_S_func_818C8FD0_4 *target_pos;
                    u16 end_time;
                    u32 tile_coord;

                    effect->unk_08 = one;
                    tile_distance = object->unk_72;
                    tile_coord = tile->unk_24;
                    if (tile_distance != tile_coord) {
                        tile_distance -= tile_coord;
                    } else {
                        tile_distance = object->unk_73;
                        tile_coord = tile->unk_25;
                        tile_distance -= tile_coord;
                    }
                    if (tile_distance < 0) {
                        tile_distance = -tile_distance;
                        effect->unk_02.s16 = tile_distance * 2;
                    } else {
                        effect->unk_02.s16 = tile_distance * 2;
                    }

                    target_pos = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object->unk_60.ptr - 0x20))->unk_08;
                    duration = effect->unk_02.s16;
                    if (duration != 0) {
                        effect->unk_60 =
                            (target_pos->unk_08.s32 - output_pos->unk_08.s32 - 0x200000) /
                            (duration - 1);
                    }
                    end_time = effect->unk_02.u16;
                    end_time += 0x3C;
                    state->unk_86 = end_time;
                } else {
                    effect->unk_02.s16 = 0x20;
                    effect->unk_08 = 0;
                    state->unk_86 = effect->unk_02.s16 + 0x1E;
                }

                effect_node->unk_10 = update_a_moving_effect_spawns_particles_advances_timed_phases;
                {
                    effect_pos = effect_node->position;

                    effect_pos->x.v = output_pos->unk_00.s32;
                    effect_pos->y.v = output_pos->unk_04.s32;
                    effect_pos->z.v = output_pos->unk_08.s32;
                    {
                        SpriteFrameState *effect_part = effect_node->sprite;

                        effect_part->color.c.b = 0x80;
                        effect_part->color.c.g = 0x80;
                        effect_part->color.c.r = 0x80;
                        effect_part->scale_y = 0x1000;
                        effect_part->scale_x = 0x1000;
                    }
                    state->unk_A8 = effect_node;
                    state->unk_AC = effect_pos;
                    state->unk_88 = 0x63;
                }
            }
            state->unk_0A.u16++;
            return;
        }
    case 3:
        if (state->unk_88 == 0x63) {
            effect_node = state->unk_A8;
            effect_pos = state->unk_AC;

            if (effect_node->flags & 0x8000) {
                state->unk_88 = 0;
            } else {
                output_pos->unk_00.s32 = effect_pos->x.v;
                output_pos->unk_04.s32 = effect_pos->y.v;
                output_pos->unk_08.s32 = effect_pos->z.v;
            }
        }
        break;
    default:
        return;
    }

    {
        u16 old_timer = state->unk_84.u16;
        s16 timer = old_timer + 1;

        state->unk_84.u16 = timer;
        if (state->unk_86 < timer) {
            s32 active_flag = moving_particle_effect_updated;

            state->unk_84.u16 = old_timer;
            if (active_flag == 0) {
                g_dungeon_status.active_actor = 0;
                ((B31_818C8FD0_S_func_818C8FD0_10 *)((u8 *)state - 2))->unk_00 |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            } else {
                moving_particle_effect_updated = 0;
            }
        }
    }
}
