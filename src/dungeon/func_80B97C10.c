#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern struct S_80083178State D_80083CE8;
extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern s16 func_800A0134();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80171E00();
extern s16 D_8006CD00[8];
/* Updates actor movement, recording the path and refreshing the tile position and height. */
void func_80171410(u8 *object_arg, void *entry_context, u8 *tile_arg, u8 *actor_arg)
{
    register u8 *object ASM_REG("$21") = object_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *tile ASM_REG("$19") = tile_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *actor = actor_arg;
    DungeonGlobalStatus *state = &dungeonStatus;
    s32 actor_flags;
    register s32 base_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 random_turn;
    s16 limit_turn;
    s32 angle;
    u16 state_flags;
    void *target_record;
    u8 *target_tile;
    state_flags = state->flags;
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    limit_turn = 0;
    if ((state_flags & 0x4000) || (*(s8 *)(actor + 0x71)) >= 0) {
        if ((*(u8 *)(actor + 0x12)) >= 2 || (func_80171E00(object, entry_context, tile, actor) << 16) == 0) {
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

    func_800A19E4(tile, actor, 3, 6, object + 0x9C);
    actor_flags = *(s32 *)(actor + 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_record = func_800A02AC(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25));
            if (target_record != 0) {
                target_tile = *((void **) (((u8 *) target_record) + (-0x14)));
                *(u16 *)(actor + 0x2A) = func_800A0818(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(target_tile
                    + 0x24), *(u8 *)(target_tile + 0x25), object + 0x98);
                {
                    u8 path_length = (*(u8 *)(actor + 0x71)) & 0x7F;
                    ASM_USE(object);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
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
            if (func_800A04F0(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor + 0x2A)) != 0) {
                *(u8 *)(actor + 0x71) &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                func_800A0E6C(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
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
                        u16 next_angle = func_800A0818(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), (s16) target_x,
                            (s16) target_y, object + 0x98);
                        *(u16 *)(actor + 0x2A) = next_angle;
                        if ((func_8009A66C((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                            *(u16 *)(actor + 0x2A) = func_800A0818(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), object + 0x98);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&D_80082E80.tileX))) - 0x24;
                    if ((func_8009FD7C(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(check_goal + 0x24),
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
                func_800A0E6C(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
                    target_record = func_800A04F0(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor
                        + 0x2A));
                    if (target_record != 0) {
                        if ((*((s32 *) (((u8 *) target_record) + 0x1C))) & 0x2000) {
                            if (func_800A0134(target_record, actor) < 0x81) {
                                if ((func_8009A540(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                    *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                    *(u8 *)(actor + 0x71) &= 0x7F;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (!((*(s32 *)(actor + 0x1C)) & 0x20000)) {
                    func_800A0E6C(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
                }
                else {
                    u8 *angle_flags = object + 0x98;
                    *(u16 *)(actor + 0x2A) = func_800A0818(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                        D_80082E80.tileX, D_80082E80.tileY, angle_flags);
                    if ((func_8009FD7C(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), D_80082E80.tileX, D_80082E80.tileY)
                         << 16) != 0) {
                        if (func_800A0134(D_800814A8, actor) < 0x81) {
                            if ((func_8009A540(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
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
        s16 turn_index = 0;
        s16 *angle_steps = D_8006CD00;
        do {
            base_angle = *(s16 *)(actor + 0x2A);

            if ((*(u16 *)(object + 0x98)) & 2) {
                angle = base_angle - angle_steps[turn_index];
            }
            else {
                angle = base_angle + angle_steps[turn_index];
            }
            if ((func_8009A66C((s16) angle, tile, actor, 0x20) << 16) > 0) {
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
                    base_angle = (s32)(((s8 *)dirStepX));
                    *(u8 *)(tile + 0x24) += *(u8 *)((u8 *)base_angle + direction);
                    *(u8 *)(tile + 0x25) += *((u8 *) (((u8 *) (((s8 *)dirStepY))) + direction));
                }
                func_8009A21C(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                break;
            }
            if (turn_index == 0) {
                if ((*((u16 *) (((u8 *) (((s8 *)&D_80082E80.tileX))) + 0))) != (*(u16 *)(tile + 0x24))) {
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    if ((func_8009A180(actor, (*((s32 *) (((u8 *) D_800814A8) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

            turn_index++;
        } while (turn_index < 8);
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
        register s16 floor_height ASM_REG("$17") = func_800BCB04(((*(u8 *)(tile + 0x24)) << 6) | 0x20, ((*(u8 *)(tile
            + 0x25)) << 6) | 0x20, (s16) ((*(u16 *)(actor + 0x88)) - 0x20));   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if (floor_height < 0x200) {
            *(u16 *)(actor + 0x88) = floor_height;
        }
    }

    return;
    return;

}
