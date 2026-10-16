/* Relink of matched dungeon/func_80CE9758; every changed retail word is a paired relocation. */
#define dungeonSelectAndAdvanceActorMove func_80154F58
#include "modules/dungeon_ovl_7f469800_p03.h"
extern s32 func_80155734(void *, s32, void *, void *);

/* Select a movement direction, move the actor, and update its path history and height. */
void func_80154F58(u8 *move_input, void *action_context, u8 *position, u8 *actor) {
    s32 near_target;
    s32 attempt;
    register u8 *x_offsets;
    s32 target_nearby = 0;
    DungeonGlobalStatus *dungeon_state;
    DungeonGlobalStatus *turn_state;
    u32 state_flags;
    u32 actor_flags;
    s32 direction_clear;
    s32 direction_offset;
    s32 move_found;
    s32 tile_mask;
    s32 base_angle;
    s16 move_angle;
    u8 next_x;
    s32 next_y;
    void *found_target;
    u8 *object;

    dungeon_state = &dungeonStatus;
    state_flags = dungeon_state->flags;
    near_target = 0;

    if ((state_flags & 0x4000) || (((T_80172F58_S_80172F58_1 *)actor)->unk_71.s >= 0)) {
        if ((((T_80172F58_S_80172F58_1 *)actor)->unk_12 >= 2) ||
            ((func_80155734(move_input, action_context, position, actor) << 16) == 0)) {
            func_800A9A0C(actor);
            return;
        }
        if (dungeon_state->unk_0C != actor) {
            return;
        }
        ((T_80172F58_S_80172F58_1 *)actor)->unk_46 = 0xC008;
        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    dungeonUpdateActorProximityFlag(position, actor, 3, 6, move_input + 0x9C);
    actor_flags = ((T_80172F58_S_80172F58_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            found_target = dungeonFindValidMonsterNeighbor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v);
            if (found_target != NULL) {
                object = ((T_80172F58_S_80172F58_3_pre *)found_target)[-1].unk_00;
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)dungeonGetRoundedFacingAndRoundingFlag(
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                    ((T_80172F58_S_80172F58_4 *)object)->unk_24, ((T_80172F58_S_80172F58_4 *)object)->unk_25, move_input + 0x98);
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            {
                s32 object_status;

                s32 random_turn;

                object_status = ((T_80172F58_S_80172F58_1 *)actor)->unk_14;
                if (!(object_status & 0x80000000)) {
                    object_status |= 0x80000000;
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_14 = object_status;
                    random_turn = func_800A6D30();
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u += (random_turn & 7) << 9;
                }
            }
        } else {
            found_target = dungeonPlaceActorAtDirectionalNeighbor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                  ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s);
            if (found_target != NULL) {
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((T_80172F58_S_80172F58_1 *)actor)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s32 direction;
                s16 target_x;
                s32 target_y;
                s16 new_angle;
                TileObject *target;

                target = &D_80082E80;
                direction = (((T_80172F58_S_80172F58_1 *)actor)->unk_45 +
                             ((s32)(((u16)D_800814A8->facing) << 16) >> 25)) & 7;
                target_x = target->tileX +
                           ((u16 *)((s8 *)dirStepX))[direction];
                target_y = target->tileY +
                           ((u16 *)((s8 *)dirStepY))[direction];
                if ((((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v == (u16)target_x) &&
                    (((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v == (u16)target_y)) {
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
                new_angle = (u16)dungeonGetRoundedFacingAndRoundingFlag(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                          target_x, (s16)target_y, move_input + 0x98);
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = new_angle;
                if ((dungeonCheckMovementClearanceAndHeight(new_angle, position, actor, 0x20) << 16) <= 0) {
                    TileObject *retry_target = &D_80082E80;

                    ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)dungeonGetRoundedFacingAndRoundingFlag(
                        ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                        retry_target->tileX, retry_target->tileY,
                        move_input + 0x98);
                }
                {
                    TileObject *check_target = &D_80082E80;

                    if ((dungeonCompareMonsterNeighborValues(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                       check_target->tileX,
                                       check_target->tileY) << 16) != 0) {
                        near_target = 1;
                    }
                }
            } else {
                dungeonRebuildMonsterReachableTiles(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
            }
        }
    } else {
        s32 kind;

        kind = ((T_80172F58_S_80172F58_2 *)position)->unk_26.s;
        if (kind >= 0 && (((T_80172F58_S_80172F58_9 *)((u8 *)D_800E2970 + kind * 0x14))->unk_0C & 2)) {
            dungeonRebuildMonsterReachableTiles(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
        } else if (!(((T_80172F58_S_80172F58_1 *)actor)->unk_46 & 0x8000)) {
            found_target = dungeonPlaceActorAtDirectionalNeighbor(actor, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v,
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                  ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s);
            if ((found_target != NULL) && (((T_80172F58_S_80172F58_3 *)found_target)->unk_1C & 0x2000) &&
                (dungeonGetActorHeightDifference(found_target, actor) < 0x81) &&
                ((dungeonCheckDiagonalSideHeight(((s32)(((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20)) << 16) != 0)) {
                ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            if (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x20000) {
                TileObject *target = &D_80082E80;
                ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = (u16)dungeonGetRoundedFacingAndRoundingFlag(
                    ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                    target->tileX, target->tileY, move_input + 0x98);
                if ((dungeonCompareMonsterNeighborValues(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                                   target->tileX, target->tileY) << 16) != 0) {
                    if (dungeonGetActorHeightDifference(D_800814A8, actor) < 0x81) {
                        direction_clear = dungeonCheckDiagonalSideHeight(
                            ((s32)(((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                            (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20));
                        if ((direction_clear << 16) != 0) {
                            ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                            return;
                        }
                    }
                }
            } else {
                dungeonRebuildMonsterReachableTiles(position, ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.s, actor, move_input + 0x98);
            }
        }
    }
    attempt = 0;
    x_offsets = (u8 *)((s8 *)dirStepX);

    do {
        base_angle = (s32)((T_80172F58_S_80172F58_1 *)actor)->unk_2A.s;
        if (((T_80172F58_S_80172F58_10 *)move_input)->unk_98 & 2) {
            {
                s32 angle_delta = (s32)D_8006CD00[attempt];

                move_angle = (s16)(base_angle - angle_delta);
            }
        } else {
            {
                s32 angle_delta = (s32)D_8006CD00[attempt];

                move_angle = (s16)(base_angle + angle_delta);
            }
        }
        if ((dungeonCheckMovementClearanceAndHeight(move_angle, position, actor, 0x20) << 16) > 0) {
            if (attempt >= 3) {
                target_nearby = near_target;

                if (target_nearby) {
                    ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
                    return;
                }
            }
            ((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u = move_angle;
            ((T_80172F58_S_80172F58_13 *)(actor + (((T_80172F58_S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v;
            ((T_80172F58_S_80172F58_13 *)(actor + (((T_80172F58_S_80172F58_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
                ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v;
            ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u++;
            func_8009A3D0(((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v, ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v,
                          (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
            direction_offset = (((T_80172F58_S_80172F58_1 *)actor)->unk_2A.u >> 8) & 0xE;
            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v +=
                *((u8 *)((u32)direction_offset + (u32)x_offsets));
            ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v += *((u8 *)((s8 *)dirStepY) + direction_offset);
            next_x = ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v;
            next_y = ((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v;
            tile_mask = 0x3000;
            if (((T_80172F58_S_80172F58_1 *)actor)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(next_x, next_y, tile_mask);
            break;
        }
        if (attempt == 0) {
            if ((((T_80172F58_S_80172F58_11 *)(((s8 *)&D_80082E80.tileX)))->unk_00 != ((T_80172F58_S_80172F58_2 *)position)->unk_24.at00u.v)
                &&
                ((s16)dungeonCheckEntityRelation(actor, ((s32)D_800814A8->unk_58) + 0x20) != 0)) {
                return;
            }
        }
        attempt++;
    } while (attempt < 8);
    move_found = attempt < 8;
    if (!move_found) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
        ((T_80172F58_S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor);
        return;
    }
    turn_state = &dungeonStatus;
    ((T_80172F58_S_80172F58_1 *)actor)->unk_46 &= 0x7FFF;
    ((T_80172F58_S_80172F58_10 *)move_input)->unk_9C.u = ((T_80172F58_S_80172F58_2 *)position)->unk_26.u;
    ((T_80172F58_S_80172F58_1 *)actor)->unk_6D.u--;
    turn_state->unk_08++;
    if (((T_80172F58_S_80172F58_1 *)actor)->unk_6D.s == 0) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_71.u &= 0x7F;
        return;
    }
    attempt = func_800BCB04((((T_80172F58_S_80172F58_2 *)position)->unk_24.at00.v << 6) | 0x20,
                      (((T_80172F58_S_80172F58_2 *)position)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((T_80172F58_S_80172F58_1 *)actor)->unk_88 - 0x20));
    if (attempt < 0x200) {
        ((T_80172F58_S_80172F58_1 *)actor)->unk_88 = attempt;
    }
    return;
}
