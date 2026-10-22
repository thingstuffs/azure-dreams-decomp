/* Troll activity state, action animation, and directional display updates. */
#include "dungeon/monster/troll/update_actor_activity_state.h"

/* Updates actor state, directional animations, and the shared activity count. */
void update_actor_activity_state(void *task, s32 task_id, void *sprite_in, void *actor_in) {
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
        if (!(((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E54;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E54))->unk_00, 0);
            break;
        case 14:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E5C;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E5C))->unk_00, 0);
            break;
        case 15:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E64;
            select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E64))->unk_00, 0);
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
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E54;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 14:
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E5C;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 15:
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E64;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        }

        if ((get_entity_effect_value(actor, 1) << 16) == 0) {
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C + 8;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C + 8))->unk_00, 0);
                break;
            case 15:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
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
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *player;
                player = &reference_tile_object;
                floor = ((T_80175050_S_80175050_1 *)sprite_in)->unk_26;
                if ((floor == player->room_index && floor >= 0) || get_tile_chebyshev_distance(player, sprite_in) < 2) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, 1);
                    }
                }
            }

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E74;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E74))->unk_00, 0);
                break;
            case 15:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                select_sprite_entry(sprite_in, ((T_80175050_S_80175050_3 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
                break;
            }
        }

        if (((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0x8000) {
            ((T_80175050_S_80175050_0 *)task)->unk_8C = update_actor_behavior;
            return;
        }
        ((T_80175050_S_80175050_3 *)((u8 *)(&g_dungeon_status)))->unk_0A++;
        ((T_80175050_S_80175050_0 *)task)->unk_9B++;

        return;

    case 2:
        if (((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0xE000) {
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
void update_actor_action_animation_state(T_80175574_Obj0 *controller, void *context, T_80175574_Obj2 *animation, T_80175574_Obj3 *actor)
{
    unsigned long table_entry;


    switch (((T_80175574_S_80175574_0 *)controller)->unk_9B) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
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
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E54;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E54;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E5C;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E5C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E64;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E64;
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
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E54;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 14:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E5C;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 15:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E64;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
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
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E7C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (((ActorRecord *)actor)->unk_64 != 0) {
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
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E7C;
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
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
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

/* Updates the display table and directional entry for kinds 13 through 15. */
void update_directional_action_display(T_801759A0_Obj0 *actor, void *context, T_801759A0_Obj2 *display_arg, T_801759A0_Obj3 *state_arg)
{
    T_801759A0_Obj2 *display = display_arg;
    T_801759A0_Obj3 *state = state_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E54;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E24;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 14:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E5C;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E2C;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + selected_table), 0);
        }
        break;

    case 15:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E64;
        } else {
            current_table = (u32)display->table2c;
            selected_table = (u32)D_80175E34;
        }
        if (current_table != selected_table) {
            *(u32 *)((u8 *)display + 0x2c) = selected_table;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
            select_sprite_entry(display, *(u8 *)((direction_index & 7) + selected_table), 0);
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
        if (display->table2c != D_80175E54 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DC4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DC4), 0);
        return;
    case 14:
        if (display->table2c != D_80175E5C ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DCC;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DCC), 0);
        return;
    case 15:
        if (display->table2c != D_80175E64 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)display + 0x2c) = (u32)&D_80175DD4;
        direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + state->value2a + 0x100) >> 9;
        select_sprite_entry(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DD4), 0);
        return;
    default:
        return;
    }

}
