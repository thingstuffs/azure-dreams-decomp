/* Relink of matched dungeon/func_80B97C10; every changed retail word is a paired relocation. */
#define dungeonCheckMovementAndInitializeAction func_80165E10
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern s32 dungeonCheckEntityRelation();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 dungeonCheckDiagonalSideHeight();
extern s32 dungeonCheckMovementClearanceAndHeight();
extern s32 dungeonCompareMonsterNeighborValues();
extern s16 dungeonGetActorHeightDifference();
extern void *dungeonFindValidMonsterNeighbor();
extern void *dungeonPlaceActorAtDirectionalNeighbor();
extern u16 dungeonGetRoundedFacingAndRoundingFlag();
extern void dungeonRebuildMonsterReachableTiles();
extern void dungeonUpdateActorProximityFlag();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80165E10(void *, void *, void *, void *);
extern s16 D_8006CD00[8];
/* Updates actor movement, recording the path and refreshing the tile position and height. */
void func_80165420(u8 *object, void *entry_context, u8 *tile, u8 *actor)
{
    DungeonGlobalStatus *state = &dungeonStatus;
    s32 actor_flags;
    s32 base_angle;
    s32 random_turn;
    s16 limit_turn;
    s16 turn_index;
    s16 angle;
    u16 state_flags;
    void *target_record;
    u8 *target_tile;
    state_flags = state->flags;
    limit_turn = 0;
    if ((state_flags & 0x4000) || (*(s8 *)(actor + 0x71)) >= 0) {
        if ((*(u8 *)(actor + 0x12)) >= 2 || (func_80165E10(object, entry_context, tile, actor) << 16) == 0) {
            func_800A9A0C(actor);

            return;
        }
        if ((*((void **) ((u8 *)state + 0xC))) == actor) {
            *(u16 *)(actor + 0x46) = 0xC008;
        }

        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    dungeonUpdateActorProximityFlag(tile, actor, 3, 6, object + 0x9C);
    actor_flags = *(s32 *)(actor + 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_record = dungeonFindValidMonsterNeighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25));
            if (target_record != 0) {
                target_tile = *((void **) (((u8 *) target_record) + (-0x14)));
                *(u16 *)(actor + 0x2A) = dungeonGetRoundedFacingAndRoundingFlag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(target_tile
                    + 0x24), *(u8 *)(target_tile + 0x25), object + 0x98);
                {
                    u8 path_length = (*(u8 *)(actor + 0x71)) & 0x7F;
                    *(u8 *)(actor + 0x71) = path_length;
                }
                return;
            }
            {
                s32 actor_state = *(s32 *)(actor + 0x14);
                base_angle = 0x80000000;
                if (actor_state >= 0) {
                    actor_state = base_angle | actor_state;
                    *(s32 *)(actor + 0x14) = actor_state;

                    random_turn = func_800A6D30();
                    *(u16 *)(actor + 0x2A) += (random_turn & 7) << 9;
                }
            }
        }
        else {
            if (dungeonPlaceActorAtDirectionalNeighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor + 0x2A)) != 0) {
                *(u8 *)(actor + 0x71) &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                dungeonRebuildMonsterReachableTiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                {
                    s32 direction = *(u8 *)(actor + 0x45);
                    s32 base_angle = *((s16 *) (((u8 *) D_800814A8) + 0x2A));
                    s32 direction_offset;
                    s32 target_x;
                    s32 target_y;
                    direction += base_angle >> 9;
                    direction_offset = (direction & 7) * 2;
                    target_x = (D_80082E80.tileX) + (*((u16 *) (((u8 *) (((s8 *)dirStepX))) + direction_offset)));
                    target_y = (D_80082E80.tileY) + (*((u16 *) (((u8 *) (((s8 *)dirStepY))) + direction_offset)));
                    if (((*(u8 *)(tile + 0x24)) == ((u16) target_x)) && ((*(u8 *)(tile + 0x25)) == ((u16) target_y))) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                    {
                        u16 next_angle = dungeonGetRoundedFacingAndRoundingFlag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), (s16) target_x,
                            (s16) target_y, object + 0x98);
                        *(u16 *)(actor + 0x2A) = next_angle;
                        if ((dungeonCheckMovementClearanceAndHeight((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                            *(u16 *)(actor + 0x2A) = dungeonGetRoundedFacingAndRoundingFlag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), object + 0x98);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                    if ((dungeonCompareMonsterNeighborValues(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(check_goal + 0x24),
                        *(u8 *)(check_goal + 0x25)) << 16) != 0) {
                        limit_turn = 1;
                    }
                }
            }
        }
    }
    else {
        {
            s8 tile_kind = *(s8 *)(tile + 0x26);
            if ((tile_kind >= 0) && (D_800E2970[tile_kind].flags & 2)) {
                dungeonRebuildMonsterReachableTiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
                    target_record = dungeonPlaceActorAtDirectionalNeighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor
                        + 0x2A));
                    if (target_record != 0) {
                        if ((*((s32 *) (((u8 *) target_record) + 0x1C))) & 0x2000) {
                            if (dungeonGetActorHeightDifference(target_record, actor) < 0x81) {
                                if ((dungeonCheckDiagonalSideHeight(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                    *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                    *(u8 *)(actor + 0x71) &= 0x7F;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (!((*(s32 *)(actor + 0x1C)) & 0x20000)) {
                    dungeonRebuildMonsterReachableTiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
                }
                else {
                    u8 *angle_flags = object + 0x98;
                    *(u16 *)(actor + 0x2A) = dungeonGetRoundedFacingAndRoundingFlag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                        D_80082E80.tileX, D_80082E80.tileY, angle_flags);
                    if ((dungeonCompareMonsterNeighborValues(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), D_80082E80.tileX, D_80082E80.tileY)
                         << 16) != 0) {
                        if (dungeonGetActorHeightDifference(D_800814A8, actor) < 0x81) {
                            if ((dungeonCheckDiagonalSideHeight(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                *(u8 *)(actor + 0x71) &= 0x7F;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    {
        turn_index = 0;
        for (; turn_index < 8; turn_index++) {
            base_angle = *(s16 *)(actor + 0x2A);

            if ((*(u16 *)(object + 0x98)) & 2) {
                base_angle -= D_8006CD00[turn_index];
                angle = base_angle;
            }
            else {
                base_angle += D_8006CD00[turn_index];
                angle = base_angle;
            }
            if ((dungeonCheckMovementClearanceAndHeight((s16) angle, tile, actor, 0x20) << 16) > 0) {
                if (turn_index >= 3) {
                    s32 turn_limited = limit_turn;
                    if (turn_limited) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                }
                *(u16 *)(actor + 0x2A) = angle;
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x74)) = *(u8 *)(tile + 0x24);
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x7C)) = *(u8 *)(tile + 0x25);
                (*(u8 *)(actor + 0x71))++;
                func_8009A3D0(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                {
                    s32 direction = ((*(u16 *)(actor + 0x2A)) >> 8) & 0xE;
                    u8 *step_x = (u8 *)dirStepX;
                    step_x += direction;
                    *(u8 *)(tile + 0x24) += *step_x;
                    *(u8 *)(tile + 0x25) += *((u8 *) (((u8 *) (((s8 *)dirStepY))) + direction));
                }
                func_8009A21C(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                break;
            }
            if (turn_index == 0) {
                if ((*((u16 *) (((u8 *) (((s8 *)&D_80082E80.tileX))) + 0))) != (*(u16 *)(tile + 0x24))) {
                    if ((dungeonCheckEntityRelation(actor, (*((s32 *) (((u8 *) D_800814A8) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

        }
        if (turn_index >= 8) {
            *(u8 *)(actor + 0x71) &= 0x7F;
            *(u16 *)(actor + 0x46) &= 0x7FFF;
            func_800A9A0C(actor);
            return;
        }

    }

    *(u16 *)(actor + 0x46) &= 0x7FFF;
    *(u8 *)(object + 0x9C) = *(u8 *)(tile + 0x26);
    (*(u8 *)(actor + 0x6D))--;
    {
        DungeonGlobalStatus *move_state = &dungeonStatus;
        (((u16)move_state->unk_08))++;
    }
    if ((*(s8 *)(actor + 0x6D)) == 0) {
        *(u8 *)(actor + 0x71) &= 0x7F;

        return;
    }
    {
        turn_index = func_800BCB04(((*(u8 *)(tile + 0x24)) << 6) | 0x20, ((*(u8 *)(tile
            + 0x25)) << 6) | 0x20, (s16) ((*(u16 *)(actor + 0x88)) - 0x20));
        if (turn_index < 0x200) {
            *(u16 *)(actor + 0x88) = turn_index;
        }
    }

    return;
    return;

}
