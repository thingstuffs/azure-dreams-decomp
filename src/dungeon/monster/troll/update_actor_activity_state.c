#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Troll activity state, action animation, and directional display updates. */
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/troll/update_actor_activity_state.h"
#include "shared/sprite_frame_state.h"

/* Updates actor state, directional animations, and the shared activity count. */
void update_actor_activity_state(void *task, s32 task_id, SpriteFrameState *sprite_in, void *actor_in) {
    u8 *next_anim_table;
    u8 *old_anim_table;
    void *starting_task;
    void *actor;
    s32 flags;
    s32 state;
    s32 kind;
    s8 floor;

    actor = actor_in;
    state = ((T_80175050_S_80175050_0 *)task)->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            sprite_in->frameTable = troll_kind13_direction_frames;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)troll_kind13_direction_frames))->unk_00, 0);
            break;
        case 14:
            sprite_in->frameTable = troll_kind14_direction_frames;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)troll_kind14_direction_frames))->unk_00, 0);
            break;
        case 15:
            sprite_in->frameTable = troll_kind15_direction_frames;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)troll_kind15_direction_frames))->unk_00, 0);
            break;
        }
        starting_task = task;
        ((T_80175050_S_80175050_3 *)((u8 *)(&g_dungeon_status)))->unk_0A--;
        ((T_80175050_S_80175050_4 *)starting_task)->unk_9B++;
        func_80171BEC_returning(starting_task, task_id, sprite_in);
        return;

    case 1:
        kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            old_anim_table = sprite_in->frameTable;
            next_anim_table = troll_kind13_direction_frames;
            if (old_anim_table != next_anim_table) {
                sprite_in->frameTable = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 14:
            old_anim_table = sprite_in->frameTable;
            next_anim_table = troll_kind14_direction_frames;
            if (old_anim_table != next_anim_table) {
                sprite_in->frameTable = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 15:
            old_anim_table = sprite_in->frameTable;
            next_anim_table = troll_kind15_direction_frames;
            if (old_anim_table != next_anim_table) {
                sprite_in->frameTable = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        }

        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                sprite_in->frameTable = troll_kind13_recovery_frames;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind13_recovery_frames))->unk_00, 0);
                break;
            case 14:
                sprite_in->frameTable = troll_kind13_recovery_frames + 8;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind13_recovery_frames + 8))->unk_00, 0);
                break;
            case 15:
                sprite_in->frameTable = troll_kind15_recovery_frames;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind15_recovery_frames))->unk_00, 0);
                break;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_64 != 0 && begin_ready_actor_directional_action(task, task_id, sprite_in, 0) != 0) {
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_25 == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(task, task_id, sprite_in, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            flags = ((T_80175050_S_80175050_2 *)actor)->unk_1C;
            if (flags & 0x100) {
                begin_pushed_actor_move(task, task_id, sprite_in, actor);
                return;
            }
            if (flags & 0x80000) {
                begin_actor_move_to_target_facing(task, task_id, sprite_in, actor);
                update_directional_action_display(task, task_id, sprite_in, actor);
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor, *(u8 **)(((u8 *)primary_actor_record) + 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *player;
                player = &reference_tile_object;
                floor = *(s8 *)&sprite_in->room_index;
                if ((floor == player->room_index && floor >= 0) || get_tile_chebyshev_distance(player, sprite_in) < 2) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, STATUS_SLEEP);
                    }
                }
            }

            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                sprite_in->frameTable = troll_kind13_recovery_frames;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind13_recovery_frames))->unk_00, 0);
                break;
            case 14:
                sprite_in->frameTable = troll_kind14_recovery_frames;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind14_recovery_frames))->unk_00, 0);
                break;
            case 15:
                sprite_in->frameTable = troll_kind15_recovery_frames;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)troll_kind15_recovery_frames))->unk_00, 0);
                break;
            }
        }

        if (sprite_in->flags & 0x8000) {
            ((T_80175050_S_80175050_0 *)task)->unk_8C = update_actor_behavior;
            return;
        }
        ((T_80175050_S_80175050_3 *)((u8 *)(&g_dungeon_status)))->unk_0A++;
        ((T_80175050_S_80175050_0 *)task)->unk_9B++;

        return;

    case 2:
        if (sprite_in->flags & 0xE000) {
            ((T_80175050_S_80175050_3 *)((u8 *)(&g_dungeon_status)))->unk_0A--;
            ((T_80175050_S_80175050_0 *)task)->unk_8C = update_actor_behavior;
        }
        return;

    default:
        return;
    }

    return;
}

/* Updates the actor's directional animation and advances its action state. */
void update_actor_action_animation_state(T_80175574_Obj0 *controller, void *context, SpriteFrameState *animation, T_80175574_Obj3 *actor)
{
    unsigned long table_entry;

    switch (((T_80175574_S_80175574_0 *)controller)->unk_9B) {
    case 0:
        if (!(animation->flags & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_base = &g_dungeon_status;

            counter_base->activity_counts.parts.pending_action_count--;
        }
        {

            switch (((ActorRecord *)actor)->unk_48) {
            default:
                break;
            case 13:
                (animation->frameTable) = troll_kind13_direction_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind13_direction_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (animation->frameTable) = troll_kind14_direction_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind14_direction_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (animation->frameTable) = troll_kind15_direction_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind15_direction_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        }
        ((T_80175574_S_80175574_0 *)controller)->unk_9B++;
        return;

    case 1:
    {
        u8 *dir_table;
        void *current_table;

        switch (((ActorRecord *)actor)->unk_48) {
        default:
            break;
        case 13:
            current_table = animation->frameTable;
            dir_table = troll_kind13_direction_frames;
            if (current_table != dir_table) {
                (animation->frameTable) = dir_table;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 14:
            current_table = animation->frameTable;
            dir_table = troll_kind14_direction_frames;
            if (current_table != dir_table) {
                (animation->frameTable) = dir_table;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 15:
            current_table = animation->frameTable;
            dir_table = troll_kind15_direction_frames;
            if (current_table != dir_table) {
                (animation->frameTable) = dir_table;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        }
    }

        if (((ActorRecord *)actor)->mp != 0) {
            switch (((ActorRecord *)actor)->unk_48) {
            case 13:
                (animation->frameTable) = troll_kind13_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind13_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (animation->frameTable) = troll_kind14_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind14_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (animation->frameTable) = troll_kind15_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind15_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (((ActorRecord *)actor)->hp_delta != 0) {
                if (begin_ready_actor_directional_action(controller, context, animation, 0) != 0) {
                    return;
                }
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            {
                s32 actor_flags = ((ActorRecord *)actor)->flags1C;

                if (actor_flags & 0x100) {
                    begin_pushed_actor_move(controller, context, animation, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    begin_actor_move_to_target_facing(controller, context, animation, actor);
                    update_directional_action_display(controller, context, animation, actor);
                    return;
                }
            }
            if (((ActorRecord *)actor)->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if (((ActorRecord *)actor)->mp == 0) {
                return;
            }
            switch (((ActorRecord *)actor)->unk_48) {
            case 13:
                (animation->frameTable) = troll_kind13_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind13_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (animation ->frameTable) = troll_kind14_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind14_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (animation ->frameTable) = troll_kind15_recovery_frames;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)troll_kind15_recovery_frames;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        }

increment_counter:
        {
            DungeonGlobalStatus *counter_base = &g_dungeon_status;

            counter_base->activity_counts.parts.pending_action_count++;
        }
increment_state:
        ((T_80175574_S_80175574_0 *)controller)->unk_9B++;
        return;

    case 2:
        if (!(animation->flags & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_base = &g_dungeon_status;

            counter_base->activity_counts.parts.pending_action_count--;
        }
        ((T_80175574_S_80175574_0 *)controller)->unk_8C = update_actor_behavior;
        return;

    default:
        return;
    }
}

/*
 * Selects Troll's normal or status frames for item kinds 13-15 and current MP, then updates
 * movement and floor traps.
 */
void update_directional_action_display(T_801759A0_Obj0 *actor, void *context, T_801759A0_Obj2 *display_arg, T_801759A0_Obj3 *state_arg)
{
    SpriteFrameState *display= display_arg;
    T_801759A0_Obj3 *state = state_arg;
    u8 *selected_table;
    u8 *current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = troll_kind13_direction_frames;
        } else {
            current_table = display->frameTable;
            selected_table = troll_frame_set_1;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;

    case 14:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = troll_kind14_direction_frames;
        } else {
            current_table = display->frameTable;
            selected_table = troll_frame_set_2;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;

    case 15:
        if ((state->flags1c & ACTOR_ASLEEP) != 0 || state->flag25 == 0) {
            current_table = display->frameTable;
            selected_table = troll_kind15_direction_frames;
        } else {
            current_table = display->frameTable;
            selected_table = troll_frame_set_3;
        }
        if (current_table != selected_table) {
            display->frameTable = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)selected_table), 0);
        }
        break;

    default:
        break;
    }

    if (update_actor_transform_from_parent(actor, context, display, state) != 0) {
        if ((check_actor_floor_trap(display, state) << 16) > 0) {
            actor->field8c = update_actor_behavior;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (display->frameTable != troll_kind13_direction_frames ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &troll_stored_path_frames;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&troll_stored_path_frames), 0);
        return;
    case 14:
        if (display->frameTable != troll_kind14_direction_frames ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &troll_frame_set;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&troll_frame_set), 0);
        return;
    case 15:
        if (display->frameTable != troll_kind15_direction_frames ||
            (state->flags1c & (ACTOR_MP_EMPTY | ACTOR_ASLEEP)) != 0) {
            return;
        }
        display->frameTable = &troll_frame_set_4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (unsigned long)&troll_frame_set_4), 0);
        return;
    default:
        return;
    }

}
