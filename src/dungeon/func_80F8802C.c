#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 func_80171F74(void *, void *, void *, void *);
extern void func_800A9A0C(void *);
extern void func_800A19E4(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void *func_800A02AC(void *, u8, u8);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A6D30(void);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A0134(void *, void *);
extern s16 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 func_8009FD7C(s32, s32, s32, s32);
extern void func_800A0E6C(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern s16 func_8009A8C0(s16, void *, void *, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern s16 func_8009A180(void *, void *);
extern s16 func_800BCB04(s32, s32, s16);

extern s16 D_8006CD00[];

/* Selects a movement direction and updates the actor's position and movement state.
 * move_data: the movement record (turn flags at +0x98, turn side at +0x9C); position_data: the grid cell
 * the actor stands on; actor_data: the actor. */
void func_8017182C(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data)
{
    u16 dungeon_flags = dungeonStatus.flags;
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
            (s16)func_80171F74(move_data, context, position_data, actor_data) == 0) {
            func_800A9A0C(actor_data);
            return;
        }
        if (dungeonStatus.unk_0C == actor_data) {
            actor_data->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    func_800A19E4(position_data, actor_data, 3, 6, &move_data->unk_9C.as_s8);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)func_800A02AC(actor_data, position_data->tileX, position_data->tileY);
            blocker = (EntityRec *)current_angle;
            if (blocker != 0) {
                EntityRec *blocker_owner = (EntityRec *)((ObjectNodeHeader *)blocker - 1)->unk_0C;
                s16 target_angle = func_800A0818(
                    position_data->tileX, position_data->tileY,
                    blocker_owner->tileX, blocker_owner->tileY,
                    &move_data->unk_98);
                actor_data->facing = target_angle;
                actor_data->unk_71 &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing += (func_800A6D30() & 7) << 9;
            }
        } else {
            if (func_800A04F0(actor_data, position_data->tileX, position_data->tileY, actor_data->facing) != 0) {
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
                        *(u16 *)((u8 *)((s8 *)dirStepX) + offset_index);
                    target_y = target_position->tileY +
                        *(u16 *)((u8 *)((s8 *)dirStepY) + offset_index);
                }

                if (position_data->tileX == (u16)target_x &&
                    position_data->tileY == (u16)target_y) {
                    actor_data->unk_71 &= 0x7F;
                    return;
                }

                turn_data = (u8 *)&move_data->unk_98;
                target_angle = func_800A0818(
                    position_data->tileX, position_data->tileY,
                    (s16)target_x, (s16)target_y, (u16 *)turn_data);
                actor_data->facing = target_angle;
                if (func_8009A8C0(target_angle, position_data, actor_data, 0x20) <= 0) {
                    actor_data->facing = func_800A0818(
                        position_data->tileX, position_data->tileY,
                        D_80082E80.tileX, D_80082E80.tileY, (u16 *)turn_data);
                }
                if (func_8009FD7C(
                        position_data->tileX, position_data->tileY,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    limit_detour = 1;
                }
            } else {
                func_800A0E6C((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                              &move_data->unk_98);
            }
        }
    } else if (position_data->unk_026 >= 0 &&
               D_800E2970[position_data->unk_026].flags & 2) {
        func_800A0E6C((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                      &move_data->unk_98);
    } else if (!(actor_data->unk_46 & 0x8000)) {
        current_angle = (s32)func_800A04F0(actor_data, position_data->tileX, position_data->tileY, actor_data->facing);
        blocker = (EntityRec *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & 0x2000) &&
            (s16)func_800A0134(blocker, actor_data) < 0x81) {
            if (func_8009A540(
                    ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                    position_data->tileX, position_data->tileY,
                    (s16)((u16)actor_data->unk_88 - 0x20)) != 0) {
                actor_data->unk_71 &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            actor_data->facing = func_800A0818(
                position_data->tileX, position_data->tileY,
                target_position->tileX, target_position->tileY, &move_data->unk_98);
            if (func_8009FD7C(
                    position_data->tileX, position_data->tileY,
                    target_position->tileX, target_position->tileY) != 0) {
                if (func_800A0134(D_800814A8, actor_data) < 0x81) {
                    if (func_8009A540(
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
            func_800A0E6C((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                          &move_data->unk_98);
        }
    }

    turn_index = 0;
    turn_table = D_8006CD00;

    do {
        turn_flags = move_data->unk_98;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (func_8009A8C0(trial_angle, position_data, actor_data, 0x20) > 0) {
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

            func_8009A3D0(
                position_data->tileX, position_data->tileY,
                (actor_data->flags1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dirStepX);
                step_offset = (*(u16 *)&actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tileX += *x_step;
                position_data->tileY += *((u8 *)((s8 *)dirStepY) + step_offset);
            }

            func_8009A21C(
                position_data->tileX, position_data->tileY,
                (actor_data->flags1C & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tileX) != *(u16 *)&position_data->tileX) {
            if (func_8009A180(actor_data,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
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
        actor_data->unk_71 &= 0x7F;
        actor_data->unk_46 &= 0x7FFF;
        func_800A9A0C(actor_data);
        return;
    }

    {
        actor_data->unk_46 &= 0x7FFF;
        move_data->unk_9C.as_u8 = position_data->unk_026;
        actor_data->unk_6D--;
        dungeonStatus.unk_08++;
    }
    if (actor_data->unk_6D == 0) {
        actor_data->unk_71 &= 0x7F;
        return;
    }

    turn_index = func_800BCB04(
        (position_data->tileX << 6) | 0x20,
        (position_data->tileY << 6) | 0x20,
        (s16)((u16)actor_data->unk_88 - 0x20));
    if (turn_index < 0x200) {
        actor_data->unk_88 = turn_index;
    }
}
