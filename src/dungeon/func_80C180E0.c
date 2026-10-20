#include "modules/dungeon_resource17_slot0.h"

void func_801738E0(void *actor_arg, void *motion_arg, void *sprite_arg, void *entity_arg)
{
    void *actor = actor_arg;
    void *motion = motion_arg;
    SpriteStatusIndexView *sprite = sprite_arg;
    void *entity = entity_arg;
    DungeonGlobalStatus *global_state;
    u8 *anim_table;
    u32 clear_mask;
    u32 entity_flags;
    u8 state;

    state = ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (sprite->unk_14 & 0x8000) {
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_90 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744FC);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_801744FC)[
                    ((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            g_dungeon_status.unk_0A--;
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 2;
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xFFFBFFFF;
        if (!(sprite->unk_14 & 0x6000)) {
            return;
        }
        {
            s32 initial_speed = 0xFFF80000;
            anim_table = ((u8 *)D_801744F4);
            ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = initial_speed;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        select_sprite_entry(
            sprite,(u8)(*(u8 *)((((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7)
                    + (u32)anim_table)),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 1:
        if (((R17_801738E0_S_801738E0_3 *)motion)->unk_14 <= 0xFFFFF) {
            ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 += 0x20000;
        }
        if (((R17_801738E0_S_801738E0_0 *)actor)->unk_90 < 0) {
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_90 = 0;
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744FC);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744FC)[
                ((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        update_actor_status_and_food(entity);

        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 2;
        return;

    case 2:
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        if ((get_entity_effect_value(entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_801744F4)[
                    ((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
            ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
            if (sprite->unk_14 & 0x8000) {
                clear_mask = ~0x200U;
                break;
            }
            {
                register struct R17_801738E0_GlobalStruct *globals;
                globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
                entity_flags = globals->counter + 1;
                globals->counter = entity_flags;
            }
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
            return;
        } else {
            global_state = &g_dungeon_status;
        }

        if (global_state->flags & 0x1000) {
            return;
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(actor, motion, sprite, entity);
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, motion, sprite, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor, motion, sprite, entity);
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_A8 = 0;
            func_80174250(actor, motion, sprite, entity);
            return;
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(
                     entity, (u8 *)D_800814A8->unk_58 + 0x20)
                 << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            TileObject *origin = &D_80082E80;
            s8 coordinate = sprite->unk_26;

            if ((((coordinate == origin->unk_026) && (coordinate >= 0)) ||
                 (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                ((generate_random_value() & 7) == 0)) {
                clear_slots_of_type(entity, 1);
            }
        }
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744F4)[
                ((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
        if (sprite->unk_14 & 0x8000) {
            clear_mask = ~0x200U;
            break;
        }
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter++;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 3:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        } else {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        }

        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744EC)[((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);

advance_state:
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 4:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0xFFF80000;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_A8 = 8;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xBFFF;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017449C);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_8017449C)[
                ((g_game_work.view.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 0x10;
        return;

    case 16:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 0x4000;
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0;
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= ~0x200;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    default:
        return;
    }

    ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = clear_mask & entity_flags;
    ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);

    return;
}
