#include "modules/dungeon_resource10_slot0.h"

void func_80173BBC(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759E8);
        select_sprite_entry(sprite_in,
            ((u8 *)D_801759E8)[((g_game_work.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                func_80174258(action, context, sprite_in, actor_in);
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                if ((check_entity_relation(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = ((s16)get_tile_chebyshev_distance(origin, sprite_in));
                    actor_to_check = actor_in;
                    if (probe_result < 2) {
                        if (!(generate_random_value(actor_in) & 7)) {
                            clear_slots_of_type(actor_in, 1);
                        }
                        actor_to_check = actor_in;
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        clear_slots_of_type(actor_in, 1);
                    }
                    actor_to_check = actor_in;
                }
            } else {
                actor_to_check = actor_in;
            }
            if ((get_entity_effect_value(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759F0);
            select_sprite_entry(sprite_in,
                ((u8 *)D_801759F0)[((g_game_work.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);
                return;
            }
            g_dungeon_status.unk_0A++;

            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = ((u8 *)D_801759F0);
        select_sprite_entry(sprite_in,
            ((u8 *)D_801759F0)[((g_game_work.view.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);
            return;
        }
        g_dungeon_status.unk_0A++;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((R10_80173BBC_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        g_dungeon_status.unk_0A--;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)func_801717F4);

        return;
    }
}
