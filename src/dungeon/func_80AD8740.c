/* Relink of matched dungeon/func_80AC6740; every changed retail word is a paired relocation. */
/* Relink of matched dungeon/func_80A9BFF8; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource08_slot0.h"
extern s32 func_80160710(void *, s32, void *, void *);

void func_8015FF40(void *move_data, void *context, void *position_data, void *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;

    if ((dungeon_flags & 0x4000) || ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)func_80160710(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.unk_0C == actor_data) {
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data,(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v));
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R08_801717F8_S_80171C34_7 *)(((R08_801717F8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R08_801717F8_S_80171C34_7 *)(((R08_801717F8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data,(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &D_80082E80;
                    s32 target_facing = ((u16)D_800814A8->facing);
                    s32 offset_index =
                        ((((R08_801717F8_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tileX +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tileY +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v == (u16)target_x &&
                    ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v == (u16)target_y) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY), turn_data));
                }
                if (((s16)compare_monster_neighbor_values(
                        ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY)) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((R08_801717F8_S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((R08_801717F8_DungeonRecord *)D_800E2970)[((R08_801717F8_S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data,(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R08_801717F8_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(target_position->tileX),(s16)(target_position->tileY), (u8 *)move_data + 0x98));
            if (((s16)compare_monster_neighbor_values(
                    ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tileX, target_position->tileY)) != 0) {
                if (((s16)get_actor_height_difference(D_800814A8, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)D_8006CD00);

    do {
        turn_flags = ((R08_801717F8_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R08_801717F8_S_80171C34_8 *)((u8 *)actor_data + (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v;
            ((R08_801717F8_S_80171C34_8 *)((u8 *)actor_data + (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v;
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v += *x_step;
                ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v),(u16)((((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tileX) != ((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00u.v) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)D_800814A8->unk_58 + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.u = ((R08_801717F8_S_80171C34_2 *)position_data)->unk_26.u;
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.unk_08++;
    }
    if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at00.v << 6) | 0x20,
        (((R08_801717F8_S_80171C34_2 *)position_data)->unk_24.at01.v << 6) | 0x20,(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}
