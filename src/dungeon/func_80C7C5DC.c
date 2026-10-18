/* Relink of matched dungeon/func_80C94010; every changed retail word is a paired relocation. */
#include "modules/dungeon_ovl_cb3000.h"
extern s32 func_80160588(void *, s32, void *, void *);

void func_8015FDDC(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    EntityRec *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->unk_71 >= 0) {
        if (((u8 *)&actor_data->unk_10)[2] >= 2 ||
            (s16)func_80160588(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.unk_0C == actor_data) {
            actor_data->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C.as_s8);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data, position_data->tileX, position_data->tileY);
            blocker = (EntityRec *)current_angle;
            if (blocker != 0) {
                EntityRec *blocker_owner = (EntityRec *)((ObjectNodeHeader *)blocker - 1)->unk_0C;
                s16 target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tileX, position_data->tileY,
                    blocker_owner->tileX, blocker_owner->tileY,
                    &move_data->unk_98);
                actor_data->facing = target_angle;
                actor_data->unk_71 &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing += (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data, position_data->tileX, position_data->tileY, actor_data->facing) != 0) {
                actor_data->unk_71 &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &D_80082E80;
                    s32 target_facing = ((u16)D_800814A8->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tileX +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tileY +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tileX == (u16)target_x &&
                    position_data->tileY == (u16)target_y) {
                    actor_data->unk_71 &= 0x7F;
                    return;
                }

                turn_data = (u8 *)&move_data->unk_98;
                target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tileX, position_data->tileY,
                    (s16)target_x, (s16)target_y, (u16 *)turn_data);
                actor_data->facing = target_angle;
                if (check_movement_clearance_and_height(target_angle, position_data, actor_data, 0x20) <= 0) {
                    actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                        position_data->tileX, position_data->tileY,
                        D_80082E80.tileX, D_80082E80.tileY, (u16 *)turn_data);
                }
                if ((s16)compare_monster_neighbor_values(
                        position_data->tileX, position_data->tileY,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                              &move_data->unk_98);
            }
        }
    } else if (position_data->unk_026 >= 0 &&
               D_800E2970[position_data->unk_026].flags & 2) {
        rebuild_monster_reachable_tiles((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                      &move_data->unk_98);
    } else if (!(actor_data->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data, position_data->tileX, position_data->tileY, actor_data->facing);
        blocker = (EntityRec *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & 0x2000) &&
            (s16)get_actor_height_difference(blocker, actor_data) < 0x81) {
            if (check_diagonal_side_height(
                    ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                    position_data->tileX, position_data->tileY,
                    (s16)((u16)actor_data->unk_88 - 0x20)) != 0) {
                actor_data->unk_71 &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                position_data->tileX, position_data->tileY,
                target_position->tileX, target_position->tileY, &move_data->unk_98);
            if ((s16)compare_monster_neighbor_values(
                    position_data->tileX, position_data->tileY,
                    target_position->tileX, target_position->tileY) != 0) {
                if (get_actor_height_difference(D_800814A8, actor_data) < 0x81) {
                    if (check_diagonal_side_height(
                            ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                            position_data->tileX,
                                position_data->tileY,
                            (s16)((u16)actor_data->unk_88 - 0x20)) != 0) {
                        actor_data->unk_71 &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                          &move_data->unk_98);
        }
    }

    turn_index = 0;
    turn_table = D_8006CD00;

    for (; turn_index < 8; turn_index++) {
        turn_flags = move_data->unk_98;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (check_movement_clearance_and_height(trial_angle, position_data, actor_data, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->unk_71 &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            /* remember the cell in the actor's trail of visited cells */
            ((u8 *)((u8 *)actor_data + (actor_data->unk_71 & 0x7F)))[0x74] = position_data->tileX;
            ((u8 *)((u8 *)actor_data + (actor_data->unk_71 & 0x7F)))[0x7C] = position_data->tileY;
            actor_data->unk_71++;

            update_map_cell_flags_with_item_limit(
                position_data->tileX, position_data->tileY,
                (actor_data->flags1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (*(u16 *)&actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tileX += *x_step;
                position_data->tileY += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags(
                position_data->tileX, position_data->tileY,
                (actor_data->flags1C & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tileX) != *(u16 *)&position_data->tileX) {
            if ((s16)check_entity_relation(actor_data,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        actor_data->unk_71 &= 0x7F;
        actor_data->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        actor_data->unk_46 &= 0x7FFF;
        move_data->unk_9C.as_u8 = position_data->unk_026;
        actor_data->unk_6D--;
        g_dungeon_status.unk_08++;
    }
    if (actor_data->unk_6D == 0) {
        actor_data->unk_71 &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (position_data->tileX << 6) | 0x20,
        (position_data->tileY << 6) | 0x20,
        (s16)((u16)actor_data->unk_88 - 0x20));
    if (turn_index < 0x200) {
        actor_data->unk_88 = turn_index;
    }
}

