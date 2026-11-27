#include "shared/audio_commands.h"
#include "dungeon/actor/spell_resource_ids_data.h"
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
#include "dungeon/effect/particle.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/system.h"

void (*const dungeon_18e8800_entry)(B31_818C8FD0_S_func_818C8FD0_1 *, B31_818C8FD0_S_func_818C8FD0_4 *, B31_818C8FD0_S_func_818C8FD0_5 *) = update_attached_effect_motion;
const B31_818C8FD0_OffsetTable interpolation_direction_offsets = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};

   /* the 0x2 bytes before arg0 in interpolate_view_parameters, addressed as arg0[-1] */

/* Apply the effect offset, update its object, and flag expired or inactive effects. */
#include "dungeon/effect/sprite/directional_entries.h"

/* Moves and animates an expanding sprite, removing it when its lifetime ends or its hidden flag is set. */
void interpolate_view_parameters(B31_818C8824_EffectState *state, ObjectPosition *position, SpriteFrameState *object)
{
    u16 life;

    position->x.v += state->x;
    position->y.v += state->y;
    moving_particle_effect_updated = 1;
    position->z.v += state->z;
    advance_sprite_animation_and_textures(object);
    object->scale_x += 0x80;
    object->scale_y += 0x80;
    life = state->life - 1;
    state->life = life;
    if ((life << 16) <= 0) {
        NODE_HEADER(state)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        NODE_HEADER(state)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* Advance effect motion and lifetime, updating its object and marking completion. */
void advance_accelerating_particle(B31_818C8924_EffectState *effect, ObjectPosition *position, SpriteFrameState *object)
{
    u16 timer;
    u16 life;

    effect->x += effect->vx;
    effect->y += effect->vy;
    effect->z += effect->vz;
    position->x.v += effect->x;
    position->y.v += effect->y;
    position->z.v += effect->z;

    moving_particle_effect_updated = 1;
    timer = effect->timer + 1;
    effect->timer = timer;
    if (!(timer & 1)) {
        advance_sprite_animation_and_textures(object);
    }

    object->scale_x += 200;
    object->scale_y += 200;

    life = effect->life - 1;
    effect->life = life;
    if ((life << 16) <= 0) {
        NODE_HEADER(effect)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        NODE_HEADER(effect)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

   /* the 0x2 bytes before arg0 in update_particle_spawning_effect, addressed as arg0[-1] */

   /* arg0 in update_particle_spawning_effect */

   /* arg1 in update_particle_spawning_effect */

   /* the 0x18 bytes before ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30 in update_particle_spawning_effect, addressed as ((B31_818C8A70_S_818C8A70_0 *)arg0)->unk_30[-1] */

/* cfail-repair: tf7-phase1-cache-v3 */

/* Updates a moving effect, spawns particles, and advances its timed phases. */
void update_particle_spawning_effect(ParticleSpawningEffectBody *effect, ObjectPosition *position) {
    s32 effect_mode;
    s16 coord;
    s16 coord_2;
    s16 phase;
    s32 effect_value;
    u8 random_value;
    s16 remaining_ticks;
    u16 burst_ticks;
    s16 fade_ticks;
    SpriteFrameState *sprite;
    ObjectPosition *target_position;
    ObjectPosition *particle_pos;
    B31_818C8A70_S_818C8A70_1 *particle_state;   /* retained from the base: holds the repeated particle-state role */
    B31_818C8FD0_S_func_818C8FD0_2 *source;
    ObjectNodeHeader *particle;

    moving_particle_effect_updated = 1;
    source = effect->source;
    if (effect->phase == 0) {
        particle = allocate_flagged_object_node(0x212);
        particle_state = NODE_BODY(particle);
        if (particle != NULL) {
            particle_state->unk_02 = 0x1A;
            particle->update_callback = advance_accelerating_particle;
            register_node(particle, project_sprite_chain);
            sprite = particle->sprite;
            sprite->tpage_abr = 0x60;
            sprite->flags |= 0xC;
            particle_pos = particle->position;
            random_value = rand();
            coord = position->x.w.i;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->x.w.i = coord;
            random_value = rand();
            coord = position->y.w.i;
            coord -= 8;
            coord += random_value & 0xF;
            particle_pos->y.w.i = coord;
            random_value = rand();
            coord = position->z.w.i;
            coord -= 4;
            coord += random_value & 7;
            particle_pos->z.w.i = coord;
            particle_state->unk_60 = (s32) (rand() + 0xFFFE0000);
            sprite = particle->sprite;
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->clut = 0x7DCF;
            sprite->flags |= 0x100;
            select_record_entry_and_value(sprite, effect_sprite_sources, 0);
        }
        remaining_ticks = effect->ticks - 1;
        effect->ticks = remaining_ticks;
        if (remaining_ticks <= 0) {
            if (effect->has_target != 0) {
                effect->phase = 1;
                effect->ticks = 0;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            } else {
                NODE_HEADER(effect)->flags |= 0x8000;
                object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            }
        }
        if ((check_adjacent_tile_height_clearance(position->x.w.i, position->y.w.i, position->z.w.i, effect->target) << 0x10) == 0) {
            position->x.v += effect->step_x;
            position->y.v += effect->step_y;
            position->z.v += effect->step_z;
        } else {
            NODE_HEADER(effect)->flags |= 0x8000;
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            return;
        }
    }
    phase = effect->phase;
    if (phase == 1) {
        burst_ticks = effect->ticks + 1;
        effect->ticks = burst_ticks;
        if ((burst_ticks & 3) == phase) {
            particle = allocate_flagged_object_node(0x212);
            particle_state = NODE_BODY(particle);
            if (particle != NULL) {
                u32 particle_z;
                u16 particle_z_base;
                particle_state->unk_02 = 0x1A;
                particle->update_callback = advance_accelerating_particle;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                sprite->tpage_abr = 0x60;
                sprite->flags |= 0xC;
                particle_pos = particle->position;
                target_position = NODE_HEADER(effect->target)->position;
                random_value = rand();
                coord = target_position->x.w.i;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->x.w.i = coord;
                random_value = rand();
                coord = target_position->y.w.i;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->y.w.i = coord;
                random_value = rand();
                random_value &= 0x1F;
                particle_z_base = target_position->z.w.i;
                random_value += 0x10;
                particle_z = (u32)particle_z_base - random_value;
                particle_pos->z.w.i = particle_z;
                particle_state->unk_58 = (s32) (rand() - 0x8000);
                particle_state->unk_5C = (s32) (rand() - 0x8000);
                particle_state->unk_60 = (s32) ((rand() + 0xFFFC0000) * 2);
                sprite = particle->sprite;
                sprite->scale_x = 0x1000;
                sprite->scale_y = 0x1000;
                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                sprite->clut = 0x7DCF;
                sprite->flags |= 0x100;
                select_record_entry_and_value(sprite, effect_sprite_sources, 0);
            }
        }
        if ((effect->ticks & 3) == 2) {
            particle = allocate_flagged_object_node(0x212);
            particle_state = NODE_BODY(particle);
            if (particle != NULL) {
                s16 particle_z;
                particle_state->unk_02 = 0x14;
                particle->update_callback = interpolate_view_parameters;
                register_node(particle, project_sprite_chain);
                sprite = particle->sprite;
                sprite->tpage_abr = 0;
                sprite->flags |= 0xC;
                particle_pos = particle->position;
                target_position = NODE_HEADER(effect->target)->position;
                random_value = rand();
                coord = target_position->x.w.i;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->x.w.i = coord;
                random_value = rand();
                coord = target_position->y.w.i;
                coord -= 0x10;
                coord += random_value & 0x1F;
                particle_pos->y.w.i = coord;
                random_value = rand();
                random_value &= 0x3F;
                coord_2 = target_position->z.w.i;
                random_value += 0x20;
                particle_z = coord_2 - random_value;
                particle_pos->z.w.i = particle_z;
                sprite = particle->sprite;
                sprite->scale_x = 0x800;
                sprite->scale_y = 0x800;
                particle_state->unk_60 = (s32) (rand() + 0xFFFE0000);
                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                sprite->clut = 0x7DC0;
                sprite->flags |= 0x100;
                select_record_entry_and_value(sprite, directional_sprite_entries, 0);
            }
        }
        if (effect->ticks >= 0x29) {
            effect->phase = 2;
            effect->ticks = 0;
            if (try_trigger_target_record_effect(source->target, 1, source) == 0) {
                s16 random_bonus;
                u32 effect_scale;
                random_bonus = generate_random_value();
                random_bonus &= 3;
                effect_scale = effect->variant;
                random_bonus += 2;
                effect_scale >>= 2;
                effect_value = effect_scale + random_bonus;
                effect_mode = 0x10;
                if (current_spell_effect_variant == 0xFF) {
                    effect_mode = 0xFF;
                }
                try_apply_confusion_status(effect->target, effect_mode, effect_value);
            }
        }
    }
    if (effect->phase == 2) {
        fade_ticks = effect->ticks + 1;
        effect->ticks = fade_ticks;
        if (fade_ticks >= 0x15) {
            NODE_HEADER(effect)->flags |= 0x8000;
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        }
    }
}

/* Updates an effect through attachment, motion, and timed cleanup. */
void update_attached_effect_motion(B31_818C8FD0_S_func_818C8FD0_1 *state, B31_818C8FD0_S_func_818C8FD0_4 *output_pos, B31_818C8FD0_S_func_818C8FD0_5 *part)
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
    B31_818C8FD0_OffsetTable *offset_source = &interpolation_direction_offsets;

    object = state->unk_00;
    offsets = *offset_source;
    offset_table = &offsets;
    one = 1;
    frame_count = state->unk_82;
    mode = (s16)state->unk_0A;
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
        state->unk_7E = (angle >> 9) & 7;
        state->unk_0A++;
    case 1:
        {
            SpriteFrameState *owner_part;
            u16 position_z;
            u16 final_z;
            u16 delta_z;

            owner_part = owner_node->unk_0C;

            if ((get_sprite_attachment_vector(owner_part->source, owner_part, delta, 0) != 0) ||
                (owner_node->unk_0C->flags & 0x8000)) {
                output_pos->unk_00.u16.unk_02 = owner_pos->unk_00.u16.unk_02;
                output_pos->unk_04.u16.unk_06 = owner_pos->unk_04.u16.unk_06;
                position_z = owner_pos->unk_08.u16.unk_0A;
                output_pos->unk_08.u16.unk_0A = position_z;

                if (!(owner_node->unk_0C->flags & 0x8000)) {
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
                    state->unk_84 = 0;
                    state->unk_0A++;
                    return;
                }
            }
            return;
        }
    case 2:
        {

            effect_node = allocate_flagged_object_node(0x12);

            if (effect_node != 0) {
                ParticleSpawningEffectBody *effect;
                s32 direction_index;
                SpriteFrameState *tile;

                effect = NODE_BODY(effect_node);

                {
                    s16 *direction_offset;

                    direction_index = state->unk_7E;
                    direction_offset = (s16 *)((u8 *)offset_table + direction_index * 4);
                    effect->step_x = (s32)direction_offset[0] << 16;
                }
                {
                    u16 *direction_offset;

                    direction_index = state->unk_7E;
                    direction_offset = (u16 *)((u8 *)offset_table + direction_index * 4);
                    effect->step_y = (s32)direction_offset[1] << 16;
                }
                effect->source = object;
                effect->target = object->target;
                effect->chain_index = ((s16)state->unk_84 - 1) / 2;
                effect->variant = state->unk_09;
                effect->direction = state->unk_7E;

                {
                    u8 *table_base = (u8 *)dir_step_x;

                    direction_index = state->unk_7E * 2;
                    tile = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object - 0x20))->unk_0C;
                    state->unk_A0 =
                        tile->tile_x + table_base[direction_index];
                }
                {
                    u8 *table_base = (u8 *)dir_step_y;

                    direction_index = state->unk_7E * 2;
                    state->unk_A1 =
                        tile->tile_y + table_base[direction_index];
                }

                if (object->target != 0) {
                    s32 tile_distance;
                    s32 duration;
                    B31_818C8FD0_S_func_818C8FD0_4 *target_pos;
                    u16 end_time;
                    u32 tile_coord;

                    effect->has_target = one;
                    tile_distance = object->unk_72;
                    tile_coord = tile->tile_x;
                    if (tile_distance != tile_coord) {
                        tile_distance -= tile_coord;
                    } else {
                        tile_distance = object->unk_73;
                        tile_coord = tile->tile_y;
                        tile_distance -= tile_coord;
                    }
                    if (tile_distance < 0) {
                        tile_distance = -tile_distance;
                        effect->ticks = tile_distance * 2;
                    } else {
                        effect->ticks = tile_distance * 2;
                    }

                    target_pos = ((B31_818C8FD0_S_func_818C8FD0_3 *)((u8 *)object->target - 0x20))->unk_08;
                    duration = effect->ticks;
                    if (duration != 0) {
                        effect->step_z =
                            (target_pos->unk_08.s32 - output_pos->unk_08.s32 - 0x200000) /
                            (duration - 1);
                    }
                    end_time = effect->ticks;
                    end_time += 0x3C;
                    state->unk_86 = end_time;
                } else {
                    effect->ticks = 0x20;
                    effect->has_target = 0;
                    state->unk_86 = effect->ticks + 0x1E;
                }

                effect_node->update_callback = update_particle_spawning_effect;
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
            state->unk_0A++;
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
        u16 old_timer = state->unk_84;
        s16 timer = old_timer + 1;

        state->unk_84 = timer;
        if (state->unk_86 < timer) {
            s32 active_flag = moving_particle_effect_updated;

            state->unk_84 = old_timer;
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
