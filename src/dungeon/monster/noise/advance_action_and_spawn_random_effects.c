#include "dungeon/monster/noise/advance_action_and_spawn_random_effects.h"
#include "shared/sprite_frame_state.h"

/* Advance the action animation and spawn pairs of effects with randomized velocities. */
void advance_action_and_spawn_random_effects(void *action, void *motion, void *sprite, ActorRecord *actor) {
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
    void *owner_sprite;
    void *effect_motion;
    SpriteFrameState *effect_sprite;
    void *effect_data;
    void *effect;
    Packed32 *direction_source = &D_80170838;

    effect_work.copy = *direction_source;
    owner = action - 0x20;
    state = ((T_80172FFC_S_80172FFC_0 *)action)->unk_9B;
    switch (state) {
    case 0:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((T_80172FFC_S_80172FFC_0 *)action)->unk_9B = 3U;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x6000);
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        return;
    }
    ((T_80172FFC_S_80172FFC_3 *)motion)->unk_14 = 0;
    ((T_80172FFC_S_80172FFC_3 *)motion)->unk_10 = 0;
    ((T_80172FFC_S_80172FFC_3 *)motion)->unk_0C = 0;
    ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 = 0U;
    ((T_80172FFC_S_80172FFC_0 *)action)->unk_9B = (u8) (((T_80172FFC_S_80172FFC_0 *)action)->unk_9B + 1);
    return;

    case 1:
    wait_tick = ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 + 1;
    ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 = wait_tick;
    if (((s16) wait_tick != 4) && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        return;
    }
    (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80174EB8;
    select_sprite_entry(sprite, D_80174EB8[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);

    ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 = 0U;
    ((T_80172FFC_S_80172FFC_0 *)action)->unk_9B = (u8) (((T_80172FFC_S_80172FFC_0 *)action)->unk_9B + 1);
    return;

    case 2:
    effect_tick = ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 + 1;
    ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 = effect_tick;
    if (((s16) effect_tick == 0x11) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 = 0U;
        ((T_80172FFC_S_80172FFC_0 *)action)->unk_9B = (u8) (((T_80172FFC_S_80172FFC_0 *)action)->unk_9B + 1);
    }
    if (((s16) ((T_80172FFC_S_80172FFC_0 *)action)->unk_96 == 0xB) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80174E90;
        select_sprite_entry(sprite, D_80174E90[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    }
    spawn_tick = ((T_80172FFC_S_80172FFC_0 *)action)->unk_96;
    if ((u32) (spawn_tick - 9) < 5U) {
        if ((s16) spawn_tick == 9) {
            play_sound_if_enabled(0x810);
        }
        directions = (u8 *)&effect_work.copy;
        position_ptr = &position;
        spawn_count = 0;
        screen_pos = (s32 *)&effect_work.out18;
        do {
            effect = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
            effect_data = effect + 0x20;
            if (effect != NULL) {
                ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_96 = 0x19;
                ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_9E = 0x19;
                ((T_80172FFC_S_80172FFC_5 *)effect)->unk_10 = &project_sprite_entries_to_quads;
                ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_A8 = motion;
                ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_94 = (u16) actor->facing;
                effect_sprite = ((T_80172FFC_S_80172FFC_5 *)effect)->unk_0C;
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
                effect_motion = ((T_80172FFC_S_80172FFC_5 *)effect)->unk_08;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_02 = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_02;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_06 = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_06;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0A = (u16) ((T_80172FFC_S_80172FFC_3 *)motion)->unk_0A;
                owner_sprite = ((T_80172FFC_S_80172FFC_8 *)owner)->unk_0C;
                if (resolve_record_orientation_or_fallback(((T_80172FFC_S_80172FFC_9 *)owner_sprite)->unk_08, owner_sprite, spawn_offset, 0) != 0) {
                    ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_02 = (u16) (((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_02
                        + spawn_offset[0]);
                    ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_06 = (u16) (((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_06
                        + spawn_offset[1]);
                    ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0A = (u16) (((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0A
                        + spawn_offset[2]);
                }
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_14 = (s32) (((0xD - (s16) ((T_80172FFC_S_80172FFC_0 *)action)->unk_96)
                    << 0x11) + 0xFFE80000);
                ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_B4 = 0xC000;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0C =
                    (s32) (((T_80172FFC_S_80172FFC_10 *)(&directions[((u16) ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_94
                    >> 7) & 0x1C]))->unk_00 << 0x11);
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_10 =
                    (s32) (((T_80172FFC_S_80172FFC_10 *)(&directions[((u16) ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_94
                    >> 7) & 0x1C]))->unk_02 << 0x11);
                random_value = rand();
                velocity_base = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0C + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0C = velocity_base;
                random_value = rand();
                velocity_base = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_10 + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_10 = velocity_base;
                random_value = rand();
                vertical_speed = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_14;
                vertical_speed += 0xFFF80000;
                vertical_speed += (random_value & 0x3FFF) << 6;
                ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_14 = vertical_speed;
                position[0] = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_02;
                position[1] = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_06;
                position[2] = ((T_80172FFC_S_80172FFC_7 *)effect_motion)->unk_0A;
                effect_depth = func_80065420(position_ptr, screen_pos, &projection_aux, &projection_flags);
                position[0] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_02;
                position[1] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_06;
                position[2] = ((T_80172FFC_S_80172FFC_3 *)motion)->unk_0A;
                effect_sprite->unk_06 = (s16) ((effect_depth - func_80065420(position_ptr,
                    screen_pos, &projection_aux, &projection_flags))
                    - (view_direction_depth_biases[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((T_80172FFC_S_80172FFC_4 *)effect_data)->unk_94
                    + 0x100) >> 9) & 7] * 2));
            }
            next_count = spawn_count + 1;
            spawn_count = next_count;
        } while (next_count < 2);
    }
    return;

    case 3:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        spend_actor_mp(actor, 0x100);
        ((T_80172FFC_S_80172FFC_0 *)action)->unk_8C = &update_actor_behavior_and_direction;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags = (u16) (actor->action_flags & 0x7FFF);
    }
    return;
    default:
        return;
    }
}
