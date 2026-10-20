#include "modules/dungeon_resource17_slot0.h"

void update_entity_item_action_and_idle_return(R17_80172C18_State *state, R17_80172C18_Position *pos, R17_80172C18_Actor *actor, R17_80172C18_Entity *ent)
{
    u8 *item_slot;
    s32 state_index;
    s16 use_main_link;
    u8 *actor_parts;
    R17_80172C18_SubActor *sub_actor;
    R17_80172C18_ActorBase *actor_base;

    use_main_link = 0;
    state_index = state->state9B;
    actor_parts = state->fA4;
    sub_actor = (R17_80172C18_SubActor *)(actor_parts + 0x20);
    actor_base = (R17_80172C18_ActorBase *)(actor_parts + 0x28);

    switch (state_index) {
    case 0:
        if (ent->flags1C & 0x2000) {
            s32 slot_index;

            slot_index = (ent->f46 & 0x3FFF) - 1;
            switch (slot_index) {
            case 6:
                use_main_link = 1;
                /* fall through */
            case 2:
                item_slot = &ent->slots[6];
                break;
            case 5:
                use_main_link = 1;
                /* fall through */
            case 1:
                item_slot = &ent->slots[3];
                break;
            case 4:
                use_main_link = 1;
                /* fall through */
            case 0:
                item_slot = &ent->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 slot_type;

            slot_type = ent->f46 & 0x3FFF;
            switch (slot_type) {
            case 3:
                item_slot = &ent->slots[6];
                break;
            case 2:
                item_slot = &ent->slots[3];
                break;
            case 1:
                item_slot = &ent->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            s32 main_link_test;
            u16 state_flags;
            u8 *link_base;
            u8 *linked_actor;

            state_flags = state->flags98;
            state_flags &= 0xFF7F;
            state->flags98 = state_flags;
            main_link_test = use_main_link;
            if (main_link_test) {
                link_base = (u8 *)((R17_80172C18_MainObj *)D_800814A8);
                ent->f60 = link_base;
                linked_actor = *(u8 **)(link_base - 0x14);
                ent->f72 = linked_actor[0x24];
                ent->f73 = linked_actor[0x25];
            } else if (D_8006DE24[*item_slot].kind == 2) {
                link_base = ent->f60;
                if (link_base != 0) {
                    linked_actor = *(u8 **)(link_base - 0x14);
                    ent->f72 = linked_actor[0x24];
                    ent->f73 = linked_actor[0x25];
                }
            } else {
                s32 offset_y;
                s32 offset_x;

                ent->f60 = scan_monster_along_heading(
                    ent,(u8)(actor->f24),(u8)(actor->f25),(s16)(ent->f2A), 0x10);
                offset_x = __builtin_abs(ent->f72);
                offset_y = __builtin_abs(ent->f73);
                ent->f72 = offset_x;
                ent->f73 = offset_y;
            }

            sub_actor->flags4 &= 0x7FFF;
            actor_base->f2C = (void (*)(void))((u8 *)D_801744E4);
            select_sprite_entry(
                actor_base,
                ((u8 *)D_801744E4)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                0);
            if (!create_actor_spell_effect(ent, item_slot, use_main_link, &state->flags98)) {
                return;
            }
            actor->flags14 &= 0xF7FF;
            create_source_positioned_object(pos, 5);
            play_sound_if_enabled(0x703);
            state->state9B++;
            state->flags98 |= 8;
            ent->flags1C &= 0xF7FFFFFF;
            ent->flags1C &= 0xFFFBFFFF;
            return;
        }

        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->f24),(u8)(actor->f25));
        {
            R17_80172C18_MainObj *main_obj;

            main_obj = ((R17_80172C18_MainObj *)D_800814A8);
            g_dungeon_status.active_actor = 0;
            main_obj->fA6--;
        }
        advance_status_timers(ent);
        ent->f6D--;
        state->f8C = (void (*)(void))((u8 *)update_entity_movement_and_ground_height);
        ent->f73 = 0;
        ent->f72 = 0;
        ent->f46 &= 0x7FFF;
        return;


    case 1:
        state->u90.h.half92 += (-0x60 - (s16)state->u90.h.half92) >> 3;
        if (actor->flags14 & 0xE000) {
            actor->f2C = (void (*)(void))((u8 *)D_801744DC);
            select_sprite_entry(
                actor,
                ((u8 *)D_801744DC)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                0);
            state->f96 = state_index;
            state->state9B++;
        }
        return;


    case 2:
        if (get_cd_command_queue_depth()) {
            actor->flags14 |= 0x800;
            return;
        }
        actor->flags14 &= 0xF7FF;
        state->state9B++;


    case 3:
        state->u90.h.half92 +=
            (-0x30 - (s16)state->u90.h.half92) >> 3;
        state->f96--;
        if ((s16)state->f96 <= 0 || (actor->flags14 & 0xE000)) {
            state->flags98 |= 0x80;
        }
        if ((!(state->flags98 & 0x4000) && state->fA8 == 2) || (actor->flags14 & 0x8000)) {
            state->flags98 |= 0x4000;
        }
        if (!(actor->flags14 & 0xE000)) {
            return;
        }

        sub_actor->flags4 |= 0x8000;
        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->f24),(u8)(actor->f25));
        state->flags98 &= 0xFFF7;
        ent->flags1C |= 0x08000000;
        ent->flags1C |= 0x00040000;

        if (actor->f2C != (void (*)(void))((u8 *)D_80174494) &&
            actor->f2C != (void (*)(void))((u8 *)D_8017449C)) {
            state->fA8 = 0;
            state->flags98 &= 0xBFFF;
            actor->f2C = (void (*)(void))((u8 *)D_80174494);
            select_sprite_entry(
                actor,
                ((u8 *)D_80174494)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                state->fA8);
        }
        {

            if (((u32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            if (!(state->flags98 & 0x4000)) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags14 &= 0xF7FF;
        state->f8C = (void (*)(void))((u8 *)update_entity_movement_and_ground_height);
        advance_status_timers(ent);
        if (ent->f6D > 0) {
            ent->f6D--;
        }
        ent->f73 = 0;
        ent->f72 = 0;
        ent->f46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    default:
        return;
    }
}
