#include "modules/dungeon_resource07_slot0.h"

void func_80170E54(void *record, EntityRec *entity, void *object, EntityRec *other_entity)
{
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;
    u8 *high_table; /* MATCH: both table-selection paths feed the shared tail in a1. */

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        advance_stored_path_motion(record, entity, object, other_entity);
        return;
    }

    if (other_entity->tileY == 0) {
        advance_actor_pending_action(record, entity, object, other_entity);
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p == ((u8 *)D_80174190)) {
            return;
        }
        {
            void *next_state;

            next_state = ((u8 *)D_80174188);
            high_table = next_state;
        }
        (*(void * *)((u8 *)object + 0x2C)) = high_table;
        func_80047784(object,
            *((u8 *)(((g_game_work.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)high_table),
            0);
        return;
    }

    if (((u32)other_entity->flags1C) & 0x200) {
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p == ((u8 *)D_80174190)) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)record)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)record)->unk_8C = 0;
            other_entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(record, entity, object, ((u8 *)D_80174188)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)other_entity->flags1C) & 0x100) {
            begin_pushed_actor_move(record, entity, object, other_entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 != 0xE) {
            table = ((u8 *)D_80174148);
            if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != table) {
                (*(void * *)((u8 *)object + 0x2C)) = table;
                func_80047784(object,
                    table[((g_game_work.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        }

        ((Rec_func_800A9E70_arg0 *)record)->unk_98 &= 0xFFF3;
        if (other_entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(record, entity, object, ((u8 *)D_80174150)) != 0) {
                return;
            }
        }

        if (((u32)other_entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(record, entity, object, other_entity);
            func_80173EF4(record, entity, object, other_entity);
            (*(void * *)((u8 *)object + 0x2C)) = ((u8 *)D_80174140);
            func_80047784(object,
                *((u8 *)(((g_game_work.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)((u8 *)D_80174140)),
                0);
            return;
        }

        if ((can_entity_gain_level(other_entity) << 16) != 0) {
            process_selected_actor_record(record, entity, object, other_entity);
        }
    }

    result = ((s8)find_active_rect_containing_point(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v, ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v));
    ((R07_80170E54_S_80170E54_2 *)object)->unk_26 = result;

    if (other_entity->unk_6D > 0) {
        if (((u32)other_entity->flags1C) & 0x20) {
            update_actor_status_and_food(other_entity);
            return;
        }
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_801717B4(record, entity, object, other_entity);
            return;
        }
        if (!(other_entity->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(other_entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017229C(record, entity, object, 0) << 16) == 0) {
                return;
            }
            state = other_entity->unk_46 | 0x4000;
            other_entity->unk_46 = state;
            if (!(state & 0x8000)) {
                func_801717B4(record, entity, object, other_entity);
                return;
            }
        }

        state = other_entity->unk_46 & 0x3FFF;
        switch (state) {
        case 8:
        case 9:
            if ((func_80171FC0(record, entity, object, other_entity) << 16) != 0) {
                return;
            }
            func_80172184(record, entity, object, other_entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 coordinate;

            coordinate = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v),(s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                &scratch));
            player = D_800814A8;
            other_entity->facing = coordinate;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(record, entity, object, ((u8 *)D_80174140), ((void *)func_80170E54));
                return;
            }
        }

        case 12:
            update_actor_status_and_food(other_entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(record, entity, object, ((u8 *)D_80174140), ((void *)func_80170E54));
            return;

        case 11:
        default:
            func_801717B4(record, entity, object, other_entity);
            return;
        }
    }

    if (!(((u32)other_entity->flags1C) & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((u32)other_entity->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v, ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    other_entity->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v),(s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                        &scratch));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((R07_80170E54_S_80170E54_2 *)object)->unk_14 & 0x40) {
        return;
    }

    table = ((u8 *)D_80174148);
    if ((((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != table) &&
        (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != ((u8 *)D_80174140))) {
        (*(void * *)((u8 *)object + 0x2C)) = table;
        func_80047784(object,
            table[((g_game_work.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = 1;
    } else if (((R07_80170E54_S_80170E54_2 *)object)->unk_14 & 0x6000) {
        s16 timer = ((Rec_func_800A9E70_arg0 *)record)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = timer;
        if (timer < 0) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_AA = (func_80069EF8() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)record)->unk_AA < 2) {
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p = ((u8 *)D_80174148);
        } else {
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p = ((u8 *)D_80174140);
        }
        func_80047784(object,
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p2[
                ((g_game_work.view.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
    }

    if (!resolve_record_orientation_or_fallback(((R07_80170E54_S_80170E54_2 *)object)->unk_08, object, offset, 1)) {
        return;
    }
    if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != ((u8 *)D_80174148)) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;
        s32 base_word;

        created = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
        ((Rec_func_800A9E70_arg0 *)record)->unk_A0.at00_pv.v = created;
        object = created;
        if (object == 0) {
            return;
        }
        func_8004491C(object, func_80045340);
        color = (void *)0x00808080;
        ((R07_80170E54_S_80170E54_2 *)object)->unk_10 = ((u8 *)D_800D79B0);
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_02 =
            ((u16)entity->x.w.i) + offset[0];
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_06 =
            ((u16)entity->y.w.i) + offset[1];
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_0A =
            ((u16)entity->z.w.i) + offset[2];
        sub = ((R07_80170E54_S_80170E54_2 *)object)->unk_0C;
        base = ((u8 *)D_800DEA68);
        ((R07_80170E54_S_80170E54_2 *)object)->unk_BB = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_1E = 0xC00;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_1C = 0xC00;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_0C = color;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_00 = base;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_14 |= 0xC;
        base_word = ((R07_80170E54_S_80170E54_8 *)base)->unk_04;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_04 = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_05 = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_08 = base_word;
    }
}

