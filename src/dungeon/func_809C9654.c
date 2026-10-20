#include "modules/dungeon_resource03_slot0.h"

void func_80170E54(void *controller, void *context, void *entity, EntityRec *actor_state)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        advance_stored_entity_path(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->tileY == 0) {
        advance_actor_pending_action(controller, context, entity, actor_state);
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C != ((u8 *)D_80173CDC)) {
            u8 *early_table = ((u8 *)D_80173CD4);
            void *record = entity;
            entity = (u8 *)entity + 0x2C;
            *(void **)entity = early_table;
            select_sprite_entry(record,
                early_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & 0x200) {
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C == ((u8 *)D_80173CDC)) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(controller, context, entity, ((u8 *)D_80173CD4))) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & 0x100) {
            begin_pushed_actor_move(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = ((u8 *)D_80173C7C);
            if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C != anim_table) {
                (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
                select_sprite_entry(entity,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor_state->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, entity, ((u8 *)D_80173C84))) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, entity, actor_state);
            func_80173A30(controller, context, entity, actor_state);
            return;
        }

        if ((s16)can_entity_gain_level(actor_state) != 0) {
            process_selected_actor_record(controller, context, entity, actor_state);
        }
    }

    room_id = find_active_rect_containing_point(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v, ((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v);
    ((R03_80170E54_S_80170E54_2 *)entity)->unk_26 = room_id;

    if (actor_state->unk_6D > 0) {
        if (((u32)actor_state->flags1C) & 0x20) {
            update_actor_status_and_food(actor_state);
            return;
        }
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            advance_actor_path_with_item_search(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor_state,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)dispatch_actor_path_state_and_relink_entity(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->unk_46 |= 0x4000;
            if (!(actor_state->unk_46 & 0x8000)) {
                advance_actor_path_with_item_search(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)check_actor_transition_and_start_effect(controller, context, entity, actor_state) == 0) {
                start_directional_actor_effect(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player_controller;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag((s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v),(s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                    &direction_flags);
                player_controller = D_800814A8;
                actor_state->facing = direction;
                if (player_controller->unk_9A != 0x11) {
                    update_actor_status_and_food(actor_state);
                    return;
                }
                begin_actor_spell_action(controller, context, entity, ((u8 *)D_80173CCC), ((void *)func_80170E54));
                return;
            }
        case 12:
            update_actor_status_and_food(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(controller, context, entity, ((u8 *)D_80173CCC), ((void *)func_80170E54));
            return;
        default:
            break;
        }

        advance_actor_path_with_item_search(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v,
                    ((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v, D_80082E80.tile_position.parts.tile_x,
                    D_80082E80.tile_position.parts.tile_y) != 0) {
                    actor_state->facing = get_rounded_facing_and_rounding_flag((s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v),(s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                        &direction_flags);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((R03_80170E54_S_80170E54_2 *)entity)->unk_14 & 0x40) {
        return;
    }
    anim_table = ((u8 *)D_80173C7C);
    if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
    select_sprite_entry(entity,
        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
