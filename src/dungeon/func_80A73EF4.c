#include "modules/dungeon_resource07_slot0.h"

void func_801736F4(void *controller, s32 actor_index, void *sprite, EntityRec *actor)
{
    DungeonGlobalStatus *dungeon_status;
    s32 actor_flags;
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174190);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_80174190)[((g_game_work.view.viewAngle
                             + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->unk_0A)--;
        }
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;

    case 1:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {
            void *anim_table;
            anim_table = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
            if (anim_table == ((u8 *)D_80174140)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)D_80174188);
            } else if (anim_table == ((u8 *)D_80174188)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)D_80174190);
            }
            select_sprite_entry(
                sprite,(u8)(((u8 *)((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv)
                    [((g_game_work.view.viewAngle
                       + actor->facing + 0x100)
                      >> 9) & 7]),
                0);
        }

        if ((get_entity_effect_value(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174188);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_80174188)[((g_game_work.view.viewAngle + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                actor->flags1C &= ~0x200;
                ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)func_80170E54);
                return;
            }
            {
                DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                (*(u16 *)&dungeon_counters->unk_0A)++;
            }
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        } else {
            dungeon_status = &g_dungeon_status;
            if (!(dungeon_status->flags & 0x1000)
                && ((actor->unk_64 == 0)
                    || (begin_ready_actor_directional_action(controller, actor_index, sprite, 0) == 0))) {

                if (actor->tileY == 0) {
                    if (dungeon_status->flags & 0x2008) {
                        return;
                    }
                    advance_actor_pending_action(controller, actor_index, sprite, actor);
                    return;
                }

                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    return;
                }
                actor_flags = actor->flags1C;
                if (actor_flags & 0x100) {
                    begin_pushed_actor_move(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    begin_actor_move_to_target_facing(controller, actor_index, sprite, actor);
                    func_80173EF4(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor->unk_6D == 0) {
                    return;
                }
                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    if ((check_entity_relation(
                             actor,
                             ((s32)D_800814A8->unk_58)
                                 + 0x20)
                         << 16)
                        != 0) {
                        return;
                    }
                }

                update_actor_status_and_food(actor);
                on_actor_status_updated(actor);
                if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                    TileObject *room_base;
                    s32 room_id;
                    room_base = &D_80082E80;
                    room_id = ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_s8;
                    if (((room_id == room_base->unk_026)
                         && (room_id >= 0))
                        || (((s16)get_tile_chebyshev_distance(room_base, sprite)) < 2)) {
                        if (!(generate_random_value() & 7)) {
                            clear_slots_of_type(actor, 1);
                        }
                    }
                }
                if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                    return;
                }

                (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174188);
                select_sprite_entry(
                    sprite,(u8)(((u8 *)D_80174188)[((g_game_work.view.viewAngle + actor->facing + 0x100)
                                >> 9) & 7]),
                    0);
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                    actor->flags1C &= ~0x200;
                    ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)func_80170E54);
                    return;
                }
                {
                    DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                    (*(u16 *)&dungeon_counters->unk_0A)++;
                }
                ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
                return;
            }
        }
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->unk_0A)--;
        }
        actor->flags1C &= ~0x200;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174188);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_80174188)[((g_game_work.view.viewAngle + actor->facing + 0x100)
                        >> 9) & 7]),
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)func_80170E54);
        return;

        return;
    }
}
