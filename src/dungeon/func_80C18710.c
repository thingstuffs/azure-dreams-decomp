#include "modules/dungeon_resource17_slot0.h"

void func_80173F10(void *action, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.unk_00;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
        direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)D_801744F4)[direction & 7]), 0);
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
            direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&g_dungeon_status.unk_00;
            ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A++;
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.unk_00;
        if (((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(action, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174250(action, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((check_entity_relation(entity,
                    (u8 *)((R17_80173F10_S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        direction = (g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_0A++;

        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.unk_00;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    }

    default:
        return;
    }
}
