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
                if ((check_entity_relation(actor, *(u8 **)(((u8 *)D_800814A8) + 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *player;
                player = &D_80082E80;
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
