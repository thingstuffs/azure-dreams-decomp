#include "shared/audio_commands.h"
/* Directional actor effects and their spiraling particle animation. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/effect/directional_actor.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/directional_actor.h"

/* Moves to a directional target, emits spiraling particles, and attempts a timed target effect before
   cleanup. */
void update_directional_actor_effect(EntityRec *effect_arg, void *motion_arg, Row_818E0800_S_818E0800_10 *actor_state)
{
    void *actor;
    void *actor_base;
    ObjectNodeHeader *entity;
    void *target;
    SpriteFrameState *render_state;
    void *particle;
    register void *sprite_set;
    s32 particles_left;
    register void *actor_data;
    register s32 timer;
    s32 initial_state;
    s32 dispatch_state;
    s32 ground_z;
    u8 * found_target;
    s32 hit_effect;

    actor = ((void *)effect_arg->x.v);
    timer = effect_arg->unk_50;
    actor_data = ((Row_818E0800_S_818E0800_1_pre *)actor)[-1].unk_00;
    timer -= 1;
    initial_state = effect_arg->z.w.i;
    effect_arg->unk_50 = timer;
    actor_base = (u8 *)actor - 0x20;

    if (initial_state == 2) {
        target = ((Row_818E0800_S_818E0800_1 *)actor)->unk_60;
        if (target == 0) {
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v =
                ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_00.at00.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v =
                ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_04.at00.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v =
                ((Row_818E0800_S_818E0800_13 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_08;
        } else {
            entity = (u8 *)target - 0x20;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v = (entity->position)->x.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v = (entity->position)->y.v;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v = (entity->position)->z.v;
        }

        particles_left = 5;
        sprite_set = directional_effect_entries;
        do {
            entity = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
            if (entity != 0) {
                register_node(entity, project_sprite_chain);
                render_state = entity->sprite;
                entity->update_callback = shrink_spiraling_sprite_effect;
                particle = (u8 *)entity + 0x20;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_0C = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_0E = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v;
                {
                    s32 particle_z;
                    particle_z = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_48 = 0;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_16 = 0;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_14 = 0;
                    particle_z += 0x10;
                    ((Row_818E0800_S_818E0800_5 *)particle)->unk_10 = particle_z;
                }
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_18 = rand();
                render_state->scale_y = 0x1000;
                render_state->scale_x = 0x1000;
                render_state->tpage_abr = 0x60;
                render_state->unk_00 = sprite_set;
                render_state->flags |= 0xC;
                render_state->source = ((Row_818E0800_S_818E0800_7 *)sprite_set)->unk_04;
                render_state->unk_04 = 0;
                render_state->frame_ticks = 0;
                ((Row_818E0800_S_818E0800_4 *)entity)->unk_20 = effect_arg;
                ((Row_818E0800_S_818E0800_5 *)particle)->unk_4C = 0;
            }
            particles_left -= 1;
        } while (particles_left >= 0);
    }

    dispatch_state = effect_arg->z.w.i;
    switch (dispatch_state) {
    case 0:
        if (!(((Row_818E0800_S_818E0800_14 *)(((void *)effect_arg->y.v)))->unk_00 & 0x80)) {
            return;
        }
        found_target = (u8 *)scan_actor_along_heading(
            actor, ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_24, ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_25,
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_2A,
            (s16)get_definition_entry_byte_13(0x23));
        ((Row_818E0800_S_818E0800_1 *)actor)->unk_60 = found_target;
        if (found_target == 0) {
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.s = ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_24;
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.s = ((Row_818E0800_S_818E0800_8 *)actor_data)->unk_25;
        } else {
            render_state = ((Row_818E0800_S_818E0800_9_pre *)found_target)[-1].unk_00;
            if (render_state->flags & 0x8000) {
                if (actor_state->unk_14 & 0x8000) {
                    effect_arg->z.w.i = 0xF0;
                    return;
                }
            }
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.s = render_state->tile_x;
            ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.s = render_state->tile_y;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_00.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_04.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v =
            ((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_0A;
        effect_arg->unk_50 = 8;

        {
            s32 delta_x = ((Row_818E0800_S_818E0800_1 *)actor)->unk_72.u;
            s32 origin_x = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v;
            delta_x <<= 6;
            origin_x -= 0x20;
            delta_x -= origin_x;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at02.v = delta_x;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at00.v /= ((s16)effect_arg->unk_50);
        {
            s32 delta_y = ((Row_818E0800_S_818E0800_1 *)actor)->unk_73.u;
            s32 origin_y = ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v - 0x20;
            delta_y <<= 6;
            delta_y -= origin_y;
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at02.v = delta_y;
        }
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at00.v /= ((s16)effect_arg->unk_50);
        ground_z = (s16)(((Row_818E0800_S_818E0800_12 *)(((Row_818E0800_S_818E0800_3 *)actor_base)->unk_08))->unk_0A - 0x30);
        ground_z = sample_terrain_surface_height(((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at02.v,
            ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at02.v, ground_z);
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at02.v = ground_z - ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at02.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at00.v /= ((s16)effect_arg->unk_50);
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        (*(u16 *)&effect_arg->z.w.i) += 1;
        return;
    case 1:
    {
        s32 next_timer;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_00.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_0C.at00.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_04.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_10.at00.v;
        ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_08.at00.v += ((Row_818E0800_S_818E0800_2 *)motion_arg)->unk_14.at00.v;
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        if (((Row_818E0800_S_818E0800_1 *)actor)->unk_60 != 0) {
            next_timer = 24;
        } else {
            next_timer = 10;
        }
        effect_arg->unk_50 = next_timer;
        (*(u16 *)&effect_arg->z.w.i) += 1;
        return;
    }
    case 2:
    {
        s32 sound_id;
        void *active_target;
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        active_target = ((Row_818E0800_S_818E0800_1 *)actor)->unk_60;
        sound_id = 8;
        if (active_target == 0) {
            effect_arg->unk_50 = 10;
            effect_arg->z.w.i = 0xFF;
            return;
        }
        initialize_timed_motion_step(sound_id, 0x10);
        effect_arg->unk_50 = 6;
        effect_arg->z.w.i = 0xF0;
        return;
    }
    case 0xF0:
        jitter_effect_position_and_fade(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, ((s16)effect_arg->unk_50));
        if (((s16)effect_arg->unk_50) == 2 &&
            !try_trigger_target_record_effect(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, 2, actor)) {
            if (((Row_818E0800_S_818E0800_15 *)(((Row_818E0800_S_818E0800_1 *)actor)->unk_60))->unk_14 & 1) {
                if (((Row_818E0800_S_818E0800_1 *)actor)->unk_60 != 0) {
                    hit_effect = (((Row_818E0800_S_818E0800_11 *)current_spell_effect_variant)->unk_00 == 0xFF) ? 0xFF : 0x10;
                    try_apply_effect_four_by_chance(((Row_818E0800_S_818E0800_1 *)actor)->unk_60, hit_effect, 2);
                }
            }
        }
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        effect_arg->z.w.i = 0xFF;
        return;
    case 0xFF:
        if (((s16)effect_arg->unk_52) & 0x8000) {
            effect_arg->unk_52 &= 0x7FFF;
            return;
        }
        if (((s16)effect_arg->unk_50) > 0) {
            return;
        }
        g_dungeon_status.active_actor = 0;
        ((Row_818E0800_S_818E0800_0_pre *)effect_arg)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}

/* Shrinks and recolors a sprite along a rotated, jittered path, looping its animation until its
   lifetime ends. */
void shrink_spiraling_sprite_effect(void *effect, Row_818E0D94_S_818E0D94_3 *position, Rec_D_80082E80 *sprite)
{
    Row_818E0D94_CallRecord transform;
    Row_818E0D94_OutputVector offset;
    Row_818E0D94_S_818E0D94_1 *effect_state;
    u16 size;
    s8 shade;

    effect_state = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_00;
    effect_state->unk_52 |= 0x8000;
    ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u16++;

    size = sprite->unk_1C.at02_u16.v - 0x50;
    sprite->unk_1C.at02_u16.v = size;
    sprite->unk_1C.at00_u16.v = size;

    {
        s32 phase;
        s32 height_jitter;
        s16 height;

        height_jitter = rand() & 0x3F;
        phase = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16 * 0x32;
        height = ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_18;
        phase += 0xC8;
        height += 0x200;
        height += height_jitter;
        ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_18 = height;
        offset.x = rsin(phase) / 80;
    }
    offset.y = 0;
    {
        s32 z_jitter;
        s32 neg_tick;

        z_jitter = rand() & 3;
        neg_tick = 0 - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16;
        offset.z = (neg_tick * 4) + z_jitter - 1;
    }

    shade = ((u8)offset.x + 0x28) - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u8;
    sprite->unk_0C.at01_s8.v = shade;
    sprite->unk_0C.at00_s8.v = shade;
    sprite->unk_0C.at02_s8.v = ((u8)offset.x + 0x60) - ((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.u8;

    transform.field0 = &offset;
    transform.field4 = &offset;
    transform.field8 = *(Row_818E0D94_Unaligned8 *)((u8 *)effect + 0x14);
    transform.field10 = *(Row_818E0D94_Unaligned8 *)((u8 *)effect + 0x0C);
    transform.field18 = 1;
    transform.field1A = 0;
    transform_rotated_vertices(&transform);

    position->unk_02 = offset.x;
    position->unk_06 = offset.y;
    position->unk_0A = offset.z;
    advance_sprite_animation_and_textures(sprite);

    if (sprite->unk_14.at00_u16.v & 0x6000) {
        sprite->unk_04.as_s8 = 0;
        sprite->unk_05.as_s8 = 0;
    }

    if (((Row_818E0D94_S_818E0D94_0 *)effect)->unk_48.s16 >= 0x20) {
        u32 *flags_base;

        ((Row_818E0D94_S_818E0D94_0_pre *)effect)[-1].unk_00 |= 0x8000;
        flags_base = (u32 *)0x80080000;
        flags_base[0x528] |= 0x8000;
    }
}
