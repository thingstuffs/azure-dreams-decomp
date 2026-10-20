#include "modules/dungeon_resource16_slot0.h"

void update_actor_state_and_dispatch_transition(void *actor, void *actor_context, void *map_object, EntityRec *creature)
{
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((R16_80171014_S_80171014_0 *)actor)->unk_9A = 0xE;
        advance_actor_path_step_and_update_counters(actor, actor_context, map_object, creature);
        return;
    }
    if (creature->tileY == 0) {
        void *animation_table;

        advance_actor_pending_action(actor, actor_context, map_object, creature);
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_2C == ((u8 *)D_8017425C)) {
            return;
        }
        animation_table = ((u8 *)D_80174254);
        (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
        select_sprite_entry(map_object,
            ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_2C == ((u8 *)D_8017425C)) {
            ((R16_80171014_S_80171014_0 *)actor)->unk_9A = 0xD;
            ((R16_80171014_S_80171014_0 *)actor)->unk_9B = 1;
            ((R16_80171014_S_80171014_0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, actor_context, map_object, ((u8 *)D_80174254)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, actor_context, map_object, creature);
            return;
        }

        {
            u8 current_state = ((R16_80171014_S_80171014_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_animation;
            void *animation_table;

            if (current_state != next_state) {
                ((R16_80171014_S_80171014_0 *)actor)->unk_9A = next_state;
            }
            current_animation = ((R16_80171014_S_80171014_2 *)map_object)->unk_2C;
            animation_table = ((u8 *)D_8017420C);
            if (current_animation != animation_table) {
                (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
                select_sprite_entry(map_object,
                    ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                    0);
                ((R16_80171014_S_80171014_2 *)map_object)->unk_05 = 1;
                ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
                ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            }
        }

        creature->flags1C |= 0x40000;
        ((R16_80171014_S_80171014_0 *)actor)->unk_98 &= 0xFFF7;

        if (creature->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, map_object, ((u8 *)D_8017421C)) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            s16 offset_delta;

            begin_actor_move_to_target_facing(actor, actor_context, map_object, creature);
            offset_delta = ((R16_80171014_S_80171014_0 *)actor)->unk_92.u - ((R16_80171014_S_80171014_0 *)actor)->unk_A2.u;
            ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_92.s = offset_delta;
            func_80173468(actor, actor_context, map_object, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, map_object, creature) << 16) != 0) {
                func_80173AE8(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v, ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v));
    ((R16_80171014_S_80171014_2 *)map_object)->unk_26 = room_id;

    if (creature->unk_6D > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            if (!(creature->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801721B4(actor, actor_context, map_object, 0) << 16) == 0) {
                    return;
                }
                action_state = creature->unk_46 | 0x4000;
                creature->unk_46 = action_state;
            }

            if (creature->unk_46 & 0x8000) {
                action_state = creature->unk_46 & 0x3FFF;
                switch (action_state - 1) {

                case 7:
                case 8:
                    if ((initialize_transition_action(actor, actor_context, map_object, creature) << 16) != 0) {
                        return;
                    }
                    begin_eligible_actor_action(actor, actor_context, map_object, creature);
                    return;

                case 4:
                case 5:
                case 6:
                    {
                        EntityRec *player;
                        s16 facing_angle;

                        facing_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v),(s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                            &distance));
                        player = D_800814A8;
                        creature->facing = facing_angle;
                        if (player->unk_9A == 0x11) {
                            begin_actor_spell_action(actor, actor_context, map_object, ((u8 *)D_8017424C), ((u8 *)update_actor_state_and_dispatch_transition));
                            return;
                        }
                    }

                case 11:
                    update_actor_status_and_food(creature);
                    return;

                case 0:
                case 1:
                case 2:
                    begin_actor_spell_action(actor, actor_context, map_object, ((u8 *)D_8017424C), ((u8 *)update_actor_state_and_dispatch_transition));
                    return;

                case 3:
                case 9:
                case 10:
                default:
                    break;
                }
            }
        }
        func_80171784(actor, actor_context, map_object, creature);
        return;
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                    ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v, ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v),(s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }
}
