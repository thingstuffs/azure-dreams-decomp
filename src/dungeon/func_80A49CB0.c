#include "modules/dungeon_resource06_slot0.h"

void update_actor_state_by_flags(void *in_actor, void *in_context, void *in_sprite, void *in_entity)
{
    void *context = in_context;
    s32 entity_flags;
    u16 stat_value;
    u16 stat_delta;
    u8 *page_base;
    s32 state;

    state = ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
        select_sprite_entry(in_sprite,(u8)(((u8 *)D_80175894)[((g_game_work.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_96 = 0;
        {
            u16 counter_value;

            counter_value = ((u16)g_dungeon_status.unk_0A);
            counter_value--;
            g_dungeon_status.unk_0A = counter_value;
        }
        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(in_entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
            select_sprite_entry(in_sprite,(u8)(((u8 *)D_80175894)[((g_game_work.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s |= 0x40000;
            if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0x8000)) {

                state = ((u16)g_dungeon_status.unk_0A);
                state++;
                g_dungeon_status.unk_0A = state;
                ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
                return;
            }
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);
            return;
        }
        page_base = (u8 *)0x80080000;

        {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(in_actor, context, in_sprite, 0) != 0) {
                    return;
                }
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_25 == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_actor, context, in_sprite, in_entity);
                return;
            }
            if ((has_pending_actor_or_turn_action(in_entity) << 16) != 0) {
                return;
            }
            entity_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u;
            if (entity_flags & 0x100) {
                begin_pushed_actor_move(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (entity_flags & 0x80000) {

                begin_actor_move_to_target_facing(in_actor, context, in_sprite, in_entity);
                stat_value = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92;
                stat_delta = ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B6 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_B8 = 0;
                ((R06_801734B0_S_801734B0_5 *)in_actor)->unk_92 = stat_value - stat_delta;
                func_80173C34(in_actor, context, in_sprite, in_entity);
                return;
            }
            if (((R06_801734B0_S_801734B0_2 *)in_entity)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(in_entity) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((check_entity_relation(in_entity,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(in_entity);
            on_actor_status_updated(in_entity);
            if ((get_entity_effect_value(in_entity, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_26;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, in_sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(in_entity, 1);
                    }
                }
            }
            if ((get_entity_effect_value(in_entity, 1) << 16) != 0) {
                return;
            }
        }
        (*(void * *)((u8 *)in_sprite + 0x2C)) = ((u8 *)D_80175894);
        select_sprite_entry(in_sprite,(u8)(((u8 *)D_80175894)[((g_game_work.view.viewAngle + ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        {
            u32 updated_flags;

            updated_flags = ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s;
            updated_flags |= 0x40000;
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.s = updated_flags;
        }
        if (((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0x8000) {
            ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;
            ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);
            return;
        }

        {

            state = ((u16)g_dungeon_status.unk_0A);
            state++;
            g_dungeon_status.unk_0A = state;
        }

        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_9B++;
        return;

    case 2:
        if (!(((R06_801734B0_S_801734B0_1 *)in_sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.unk_0A--;
        }

        ((R06_801734B0_S_801734B0_2 *)in_entity)->unk_1C.u &= ~0x200;

        ((R06_801734B0_S_801734B0_0 *)in_actor)->unk_8C = ((u8 *)initialize_destination_state);

        return;
    }
}
