#include "dungeon/monster/troll/update_actor_activity_state.h"

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

            counter_base->unk_0A--;
        }
        {

            switch (((EntityRec *)actor)->unk_48) {
            default:
                break;
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E54;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E54;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E5C;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E5C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E64;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
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

        switch (((EntityRec *)actor)->unk_48) {
        default:
            break;
        case 13:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E54;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
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
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
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
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        }
    }

        if (((EntityRec *)actor)->tileY != 0) {
            switch (((EntityRec *)actor)->unk_48) {
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
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
            if (((EntityRec *)actor)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(controller, context, animation, 0) != 0) {
                    return;
                }
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            {
                s32 actor_flags = ((EntityRec *)actor)->flags1C;

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
            if (((EntityRec *)actor)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if (((EntityRec *)actor)->tileY == 0) {
                return;
            }
            switch (((EntityRec *)actor)->unk_48) {
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                select_sprite_entry(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
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

            counter_base->unk_0A++;
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

            counter_base->unk_0A--;
        }
        ((T_80175574_S_80175574_0 *)controller)->unk_8C = update_actor_behavior;
        return;

    default:
        return;
    }
}
