#include "shared/object_node.h"
#include "shared/entity.h"
#include "dungeon/monster/noise/advance_action_and_spawn_random_effects.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/monster/blume.h"

/* Advance the action animation and spawn pairs of effects with randomized velocities. */
/* Times Noise's attack, emits particle pairs on ticks 9-13, resolves damage at tick 11, and spends MP on
 * completion. */
void advance_action_and_spawn_random_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 spawn_offset[3];
    u16 position[3];
    T_80172FFC_WorkMid effect_work;
    s32 projection_aux;
    s32 projection_flags;
    void *owner;
    u16 spawn_count;                                       /* compiler-managed */
    u8 *directions;
    u16 *position_ptr;
    s32 *screen_pos;
    s16 next_count;
    s32 effect_depth;
    s32 random_value;
    s32 velocity_base;
    s32 vertical_speed;
    u16 effect_tick;
    u16 wait_tick;
    u16 spawn_tick;
    u8 animation;
    s32 state;
    T_80172FFC_S_80172FFC_9 *owner_sprite;
    ObjectPosition *effect_motion;
    SpriteFrameState *effect_sprite;
    T_80172FFC_S_80172FFC_4 *effect_data;
    ObjectNodeHeader *effect;
    Packed32 *direction_source = &D_80170838;

    effect_work.copy = *direction_source;
    owner = ((ObjectNodeHeader *)action - 1);
    state = action->action_phase.u;
    switch (state) {
    case 0:
    if (sprite->flags & 0x8000) {
        action->action_phase.u = 3U;
        sprite->flags = (u16) (sprite->flags | 0x6000);
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        return;
    }
    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    action->action_timer.u = 0U;
    action->action_phase.u = (u8) (action->action_phase.u + 1);
    return;

    case 1:
    wait_tick = action->action_timer.u + 1;
    action->action_timer.u = wait_tick;
    if (((s16) wait_tick != 4) && !(sprite->flags & 0x8000)) {
        return;
    }
    (sprite->frameTable) = &noise_frame_set_1;
    select_sprite_entry(sprite, noise_frame_set_1[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);

    action->action_timer.u = 0U;
    action->action_phase.u = (u8) (action->action_phase.u + 1);
    return;

    case 2:
    effect_tick = action->action_timer.u + 1;
    action->action_timer.u = effect_tick;
    if (((s16) effect_tick == 0x11) || (sprite->flags & 0x8000)) {
        action->action_timer.u = 0U;
        action->action_phase.u = (u8) (action->action_phase.u + 1);
    }
    if (((s16) action->action_timer.u == 0xB) || (sprite->flags & 0x8000)) {
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
    }
    if (sprite->flags & 0xE000) {
        (sprite->frameTable) = &D_80174E90;
        select_sprite_entry(sprite, D_80174E90[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    }
    spawn_tick = action->action_timer.u;
    if ((u32) (spawn_tick - 9) < 5U) {
        if ((s16) spawn_tick == 9) {
            play_sound_if_enabled(0x810);
        }
        directions = (u8 *)&effect_work.copy;
        position_ptr = &position;
        spawn_count = 0;
        screen_pos = (s32 *)&effect_work.out18;
        do {
            effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
            effect_data = ((void *)effect) + 0x20;
            if (effect != NULL) {
                effect_data->unk_96 = 0x19;
                effect_data->unk_9E = 0x19;
                effect->update_callback = &project_sprite_entries_to_quads;
                effect_data->unk_A8 = motion;
                effect_data->unk_94 = (u16) actor->facing;
                effect_sprite = effect->sprite;
                *(T_80172FFC_S_80172FFC_6 *)effect_sprite = *(T_80172FFC_S_80172FFC_6 *)sprite;
                effect_sprite->scale_y = 0;
                effect_sprite->scale_x = 0;
                effect_sprite->color.c.b = 0x80;
                effect_sprite->color.c.g = 0x80;
                effect_sprite->color.c.r = 0x80;
                register_node(effect, project_sprite_chain);
                animation = D_80174EC0;
                effect_sprite->frameTable = &D_80174EC0;
                select_sprite_entry(effect_sprite, animation, 0);
                effect_motion = effect->position;
                effect_motion->x.w.i = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_02;
                effect_motion->y.w.i = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_06;
                effect_motion->z.w.i = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_0A;
                owner_sprite = ((T_80172FFC_S_80172FFC_8 *)owner)->unk_0C;
                if (resolve_record_orientation_or_fallback(owner_sprite->unk_08, owner_sprite, spawn_offset, 0) != 0) {
                    effect_motion->x.w.i = (u16) (*(u16 *)&effect_motion->x.w.i
                        + spawn_offset[0]);
                    effect_motion->y.w.i = (u16) (*(u16 *)&effect_motion->y.w.i
                        + spawn_offset[1]);
                    effect_motion->z.w.i = (u16) (*(u16 *)&effect_motion->z.w.i
                        + spawn_offset[2]);
                }
                effect_motion->velocity_z = (s32) (((0xD - (s16) action->action_timer.u)
                    << 0x11) + 0xFFE80000);
                effect_data->unk_B4 = 0xC000;
                effect_motion->velocity_x =
                    (s32) (((T_80172FFC_S_80172FFC_10 *)(&directions[((u16) effect_data->unk_94
                    >> 7) & 0x1C]))->unk_00 << 0x11);
                effect_motion->velocity_y =
                    (s32) (((T_80172FFC_S_80172FFC_10 *)(&directions[((u16) effect_data->unk_94
                    >> 7) & 0x1C]))->unk_02 << 0x11);
                random_value = rand();
                velocity_base = effect_motion->velocity_x + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                effect_motion->velocity_x = velocity_base;
                random_value = rand();
                velocity_base = effect_motion->velocity_y + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                effect_motion->velocity_y = velocity_base;
                random_value = rand();
                vertical_speed = effect_motion->velocity_z;
                vertical_speed += 0xFFF80000;
                vertical_speed += (random_value & 0x3FFF) << 6;
                effect_motion->velocity_z = vertical_speed;
                position[0] = *(u16 *)&effect_motion->x.w.i;
                position[1] = *(u16 *)&effect_motion->y.w.i;
                position[2] = *(u16 *)&effect_motion->z.w.i;
                effect_depth = RotTransPers(position_ptr, screen_pos, &projection_aux, &projection_flags);
                position[0] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_02;
                position[1] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_06;
                position[2] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_0A;
                effect_sprite->depth_bias = (s16) ((effect_depth - RotTransPers(position_ptr,
                    screen_pos, &projection_aux, &projection_flags))
                    - (view_direction_depth_biases[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) effect_data->unk_94
                    + 0x100) >> 9) & 7] * 2));
            }
            next_count = spawn_count + 1;
            spawn_count = next_count;
        } while (next_count < 2);
    }
    return;

    case 3:
    if (sprite->flags & 0xE000) {
        spend_actor_mp(actor, 0x100);
        action->unk_8C.handler = &update_actor_behavior_and_direction;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
    }
    return;
    default:
        return;
    }
}
