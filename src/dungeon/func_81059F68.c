#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80171F24();

extern s16 D_8006CD00[8];
extern u8 D_80082E80[];
extern s8 D_80082EA4;

/* Updates actor movement, choosing a direction and recording its path. */
void func_80171768(u8 *move_work, void *entry_context, u8 *position, u8 *actor)
{
    s32 limit_turn;
    s16 step_index;
    s16 *angle_steps;
    DungeonGlobalStatus *state;
    void *target_link;
    u16 state_flags;
    s32 actor_flags;
    s32 current_angle;
    s32 turn_limit;
    s32 trial_angle;
    s32 turn_flags;

    state = &dungeonStatus;
    state_flags = U16_AT(state, 2);
    limit_turn = 0;

    if ((state_flags & 0x4000) || S8_AT(actor, 0x71) >= 0) {
        if (U8_AT(actor, 0x12) >= 2 ||
            (func_80171F24(move_work, entry_context, position, actor) << 16) == 0) {
            func_800A9A0C(actor);
            return;
        }
        if (PTR_AT(state, 0xC) == actor) {
            U16_AT(actor, 0x46) = 0xC008;
        }
        return;
    }

    if (!(state_flags & 0x2000)) {
        return;
    }

    func_800A19E4(position, actor, 3, 6, move_work + 0x9C);
    actor_flags = S32_AT(actor, 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_link = func_800A02AC(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
            if (target_link != 0) {
                turn_flags = (s32)PTR_AT(target_link, -0x14);

                U16_AT(actor, 0x2A) = func_800A0818(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    U8_AT(turn_flags, 0x24), U8_AT(turn_flags, 0x25), move_work + 0x98);
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }
            {
                turn_flags = S32_AT(actor, 0x14);

                if (!(turn_flags & 0x80000000)) {
                    S32_AT(actor, 0x14) = turn_flags | 0x80000000;
                    turn_limit = func_800A6D30();
                    current_angle = U16_AT(actor, 0x2A) + ((turn_limit & 7) << 9);
                    U16_AT(actor, 0x2A) = current_angle;
                }
            }
        } else {
            if (func_800A04F0(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                              S16_AT(actor, 0x2A)) != 0) {
                U8_AT(actor, 0x71) &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (U16_AT(actor, 0x46) & 0x8000) {
        } else if (!(actor_flags & 0x20000)) {
            func_800A0E6C(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
        } else {
            {
                s32 direction;
                s32 offset;
                s32 target_x;
                s32 target_y;
                u8 *target = D_80082E80;

                direction = (U8_AT(actor, 0x45) +
                             ((s32)(U16_AT(D_800814A8, 0x2A) << 16) >> 25)) & 7;
                offset = direction * 2;
                target_x = U8_AT(target, 0x24) + U16_AT(((s8 *)dirStepX), offset);
                target_y = U8_AT(target, 0x25) + U16_AT(((s8 *)dirStepY), offset);
                if ((U8_AT(position, 0x24) == (u16)target_x) &&
                    (U8_AT(position, 0x25) == (u16)target_y)) {
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                }

                {
                    u8 *angle_work = move_work + 0x98;
                    s16 next_angle = func_800A0818(
                        U8_AT(position, 0x24), U8_AT(position, 0x25),
                        (s16)target_x, (s16)target_y, angle_work);

                    U16_AT(actor, 0x2A) = next_angle;
                    if ((func_8009A66C(next_angle, position, actor, 0x20) << 16) <= 0) {
                        u8 *fallback = (u8 *)&D_80082EA4 - 0x24;

                        U16_AT(actor, 0x2A) = func_800A0818(
                            U8_AT(position, 0x24), U8_AT(position, 0x25),
                            U8_AT(fallback, 0x24), U8_AT(fallback, 0x25), angle_work);
                    }
                }
            }
            {
                u8 *target = (u8 *)&D_80082EA4 - 0x24;

                if ((func_8009FD7C(
                         U8_AT(position, 0x24), U8_AT(position, 0x25),
                         U8_AT(target, 0x24), U8_AT(target, 0x25)) << 16) != 0) {
                    limit_turn = 1;
                }
            }
        }
    } else {
        s32 tile_kind;
        s32 offset;
        u8 *tile_table;

        tile_kind = S8_AT(position, 0x26);
        if (tile_kind >= 0) {
            tile_table = (u8 *)D_800E2970;
            offset = tile_kind * 0x14;
            offset += (s32)tile_table;
        }
        if (tile_kind >= 0 && (U16_AT((u8 *)offset, 0xC) & 2)) {
            func_800A0E6C(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
        } else
            if (U16_AT(actor, 0x46) & 0x8000) {
            } else {
                target_link = func_800A02AC(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
                if (!(U16_AT(move_work, 0x98) & 0x8000)) {
                } else if (target_link == 0) {
                } else if ((func_8009A540(
                         ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                         U8_AT(position, 0x24), U8_AT(position, 0x25),
                         (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                    turn_flags = (s32)PTR_AT(target_link, -0x14);

                    U16_AT(actor, 0x2A) = func_800A0818(
                        U8_AT(position, 0x24), U8_AT(position, 0x25),
                        U8_AT(turn_flags, 0x24), U8_AT(turn_flags, 0x25), move_work + 0x98);
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                } else {
                    if (func_800A04F0(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                                      S16_AT(actor, 0x2A)) != 0) {
                        if ((func_8009A540(
                                 ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                                 (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                            U8_AT(actor, 0x71) &= 0x7F;
                            return;
                        }
                    }
                    if (!(S32_AT(actor, 0x1C) & 0x20000)) {
                        func_800A0E6C(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);
                    } else {
                        u8 *goal = (u8 *)&D_80082EA4 - 0x24;
                        u8 *angle_work = move_work + 0x98;

                        U16_AT(actor, 0x2A) = func_800A0818(
                            U8_AT(position, 0x24), U8_AT(position, 0x25),
                            U8_AT(goal, 0x24), U8_AT(goal, 0x25), angle_work);
                        if ((func_8009FD7C(
                                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                                 U8_AT(goal, 0x24), U8_AT(goal, 0x25)) << 16) != 0) {
                            if ((func_8009A540(
                                     ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                                     U8_AT(position, 0x24), U8_AT(position, 0x25),
                                     (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
                                U8_AT(actor, 0x71) &= 0x7F;
                                return;
                            }
                        }
                    }
                }
            }
    }

    step_index = 0;
    angle_steps = D_8006CD00;

    for (; step_index < 8; step_index++) {
        current_angle = S16_AT(actor, 0x2A);
        if (U16_AT(move_work, 0x98) & 2) {
            trial_angle = current_angle - angle_steps[step_index];
        } else {
            trial_angle = current_angle + angle_steps[step_index];
        }
        if ((func_8009A66C((s16)trial_angle, position, actor, 0x20) << 16) > 0) {
            if (step_index >= 3) {
                turn_limit = limit_turn;
                if (turn_limit != 0) {
                    U8_AT(actor, 0x71) &= 0x7F;
                    return;
                }
            }
            U16_AT(actor, 0x2A) = trial_angle;
            {
                u8 *path_slot;

                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x74) = U8_AT(position, 0x24);
                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x7C) = U8_AT(position, 0x25);
            }
            U8_AT(actor, 0x71)++;

            func_8009A3D0(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);

            {
                s32 move_offset = (U16_AT(actor, 0x2A) >> 8) & 0xE;
                s32 step = (s32)dirStepX;

                step += move_offset;
                U8_AT(position, 0x24) += *(u8 *)step;
                U8_AT(position, 0x25) += U8_AT(((s8 *)dirStepY), move_offset);
            }
            func_8009A21C(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if ((step_index == 0) &&
            (U16_AT(&D_80082EA4, 0) != U16_AT(position, 0x24)) &&
            ((func_8009A180(
                  actor, S32_AT(D_800814A8, 0x58) + 0x20) << 16) != 0)) {
            return;
        }
    }

    if (step_index >= 8) {
        U8_AT(actor, 0x71) &= 0x7F;
        U16_AT(actor, 0x46) &= 0x7FFF;
        func_800A9A0C(actor);
        return;
    }

    U16_AT(actor, 0x46) &= 0x7FFF;
    U8_AT(move_work, 0x9C) = U8_AT(position, 0x26);
    U8_AT(actor, 0x6D)--;
    {
        DungeonGlobalStatus *move_state = &dungeonStatus;

        U16_AT(move_state, 8)++;
    }
    if (S8_AT(actor, 0x6D) == 0) {
        U8_AT(actor, 0x71) &= 0x7F;
        return;
    }

    step_index = func_800BCB04(
        (U8_AT(position, 0x24) << 6) | 0x20,
        (U8_AT(position, 0x25) << 6) | 0x20,
        (s16)(U16_AT(actor, 0x88) - 0x20));
    if (step_index < 0x200) {
        U16_AT(actor, 0x88) = step_index;
    }
    return;
}
