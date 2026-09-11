#include "common.h"
#include "records/Rec_D_800814A8.h"
extern int abs(int);

typedef struct S_801715F4_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_801715F4_0;   /* global in func_801715F4 */

typedef struct S_801715F4_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_801715F4_1;   /* arg3 in func_801715F4 */

typedef struct S_801715F4_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_801715F4_2;   /* arg2 in func_801715F4 */

typedef struct S_801715F4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801715F4_3_pre;   /* the 0x14 bytes before found in func_801715F4, addressed as found[-1] */

typedef struct S_801715F4_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_801715F4_3;   /* found in func_801715F4 */

typedef struct S_801715F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_4;   /* other in func_801715F4 */


typedef struct S_801715F4_6 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_801715F4_6;   /* monster_table + index * 0x14 in func_801715F4 */

typedef struct S_801715F4_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_7;   /* held_origin in func_801715F4 */

typedef struct S_801715F4_8 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_801715F4_8;   /* arg0 in func_801715F4 */

typedef struct S_801715F4_9 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_801715F4_9;   /* counter_state in func_801715F4 */

typedef struct S_801715F4_10 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801715F4_10;   /* (u8 *)arg3 + (((S_801715F4_1 *)arg3)->unk_71.u & 0x7F) in func_801715F4 */



extern s32 func_8009A180(void *, void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_8009A540(s32, u8, u8, s16);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0134(void *, void *);
extern void *func_800A02AC(void *, u8, u8);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A0E6C(void *, s8, void *, void *);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern s32 func_800A6D30(void);
extern s16 func_800A6E8C(void *, s32, s16 *, s16 *);
extern void func_800A9A0C(void *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_80171EBC(void *, void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s8 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_b[];
__asm__(".set D_80082E80_b, 0x80082E80");
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

/* Chooses a movement direction, advances the actor, and updates its movement history. */
void func_801715F4(void *move_state, void *caller_context, void *position_arg, void *actor_arg) {
    void *actor;
    register void *position ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 target_x;
    s16 target_y;
    s16 turn_index;
    s32 next_angle;
    s32 limit_turns;
    s32 flags;
    s32 follow_x;
    s32 follow_y;
    s32 target_x_wide;
    s32 dx;
    s32 dy;
    u32 table_offset;
    void *found;
    u8 *dungeon_state = (u8 *)&D_80083460;
    u8 *angle_context;
    u8 *leader_position;
    u8 *follow_context;
    s16 *turn_table;

    position = position_arg;
    actor = actor_arg;
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    limit_turns = 0;
    flags = ((S_801715F4_0 *)dungeon_state)->unk_02;
    if ((flags & 0x4000) || (((S_801715F4_1 *)actor)->unk_71.s >= 0)) {
        if ((((S_801715F4_1 *)actor)->unk_12 >= 2) ||
            ((s16)func_80171EBC(move_state, caller_context, position, actor) == 0)) {
            func_800A9A0C(actor);
            goto end;
        }
        if (((S_801715F4_0 *)dungeon_state)->unk_0C == actor) {
            ((S_801715F4_1 *)actor)->unk_46 = 0xC008;
        }
        goto end;
    }

    if (!(flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(position, actor, 3, 6, (u8 *)move_state + 0x9C);
    flags = ((S_801715F4_1 *)actor)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            found = func_800A02AC(actor, ((S_801715F4_2 *)position)->unk_24.at00.v,
                                  ((S_801715F4_2 *)position)->unk_24.at01.v);
            if (found != 0) {
                S_801715F4_4 *other = ((S_801715F4_3_pre *)found)[-1].unk_00;

                ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
                    other->unk_24, other->unk_25,
                    (u8 *)move_state + 0x98);
                ((S_801715F4_1 *)actor)->unk_71.u &= 0x7F;
                goto end;
            }
            {
                s32 sign_mask = 0x80000000;
                register s32 state_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                state_flags = ((S_801715F4_1 *)actor)->unk_14;
                if (state_flags >= 0) {
                    state_flags |= sign_mask;
                    ((S_801715F4_1 *)actor)->unk_14 = state_flags;
                    ((S_801715F4_1 *)actor)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            goto reset_turn_index;
        }

        found = func_800A04F0(actor, ((S_801715F4_2 *)position)->unk_24.at00.v,
                              ((S_801715F4_2 *)position)->unk_24.at01.v,
                              ((S_801715F4_1 *)actor)->unk_2A.s);
        if (found == 0) {
            goto reset_turn_index;
        }
        goto clear_history;
    }

    if (flags & 0x2000) {
        turn_index = 0;
        if (((S_801715F4_1 *)actor)->unk_46 & 0x8000) {
            goto loop_setup;
        }

        if (flags & 0x20000) {
            {
                u8 *leader;
                u32 follow_offset;

                leader = D_80082E80;
                follow_offset =
                    ((((S_801715F4_1 *)actor)->unk_45 +
                      ((s32)(((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 16) >> 25)) &
                     7) *
                    2;

                follow_x = leader[0x24] + *(u16 *)((u8 *)&D_8006CCD8 + follow_offset);
                follow_y = leader[0x25] + *(u16 *)((u8 *)&D_8006CCE8 + follow_offset);
            }
            target_x = follow_x;
            target_y = follow_y;

            if ((((S_801715F4_2 *)position)->unk_24.at00.v == (u16)follow_x) &&
                (((S_801715F4_2 *)position)->unk_24.at01.v == (u16)follow_y)) {
                goto clear_history;
            }

            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
                ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v, target_x, target_y,
                angle_context = (u8 *)move_state + 0x98);
            if (func_8009A66C(((S_801715F4_1 *)actor)->unk_2A.s, position, actor, 0x20) <=
                0) {
                ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
                    ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
                    D_80082E80_b[0x24], D_80082E80_b[0x25],
                    angle_context);
            }
            {
                s16 path_ok = func_8009FD7C(((S_801715F4_2 *)position)->unk_24.at00.v,
                                             ((S_801715F4_2 *)position)->unk_24.at01.v,
                                             D_80082E80_b[0x24],
                                             D_80082E80_b[0x25]);

                ASM_UNDEF(turn_index);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                turn_index = 0;
                if (path_ok == 0) {
                    goto loop_setup;
                }
            }
            limit_turns = 1;
            goto loop_setup;
        }
        goto call_obstacle;
    }

    turn_index = func_800A6E8C(position, 0x12, &target_x, &target_y);
    if (((S_801715F4_2 *)position)->unk_26.s >= 0) {
        s32 monster_index = ((S_801715F4_2 *)position)->unk_26.s;
        u8 *monster_table = D_800E2970;

        if (((S_801715F4_6 *)(monster_table + monster_index * 0x14))->unk_0C & 2) {
            goto call_obstacle;
        }
    }

    if (((S_801715F4_1 *)actor)->unk_46 & 0x8000) {
        goto reset_turn_index;
    }

    found = func_800A04F0(actor, ((S_801715F4_2 *)position)->unk_24.at00.v,
                          ((S_801715F4_2 *)position)->unk_24.at01.v, ((S_801715F4_1 *)actor)->unk_2A.s);
    if ((found != 0) && (((S_801715F4_3 *)found)->unk_1C & 0x2000) &&
        (func_800A0134(found, actor) < 0x81) &&
        ((s16)func_8009A540(
             ((s32)(((S_801715F4_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
             ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
             (s16)(((S_801715F4_1 *)actor)->unk_88 - 0x20)) != 0)) {
        goto clear_history;
    }

    if (((S_801715F4_1 *)actor)->unk_1C & 0x20000) {
        follow_context = (u8 *)move_state + 0x98;
        leader_position = D_80082E80;
        ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
            ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
            ((S_801715F4_7 *)leader_position)->unk_24, ((S_801715F4_7 *)leader_position)->unk_25,
            follow_context);
        if ((s16)func_8009FD7C(((S_801715F4_2 *)position)->unk_24.at00.v,
                                ((S_801715F4_2 *)position)->unk_24.at01.v,
                                ((S_801715F4_7 *)leader_position)->unk_24,
                                ((S_801715F4_7 *)leader_position)->unk_25) == 0) {
            goto reset_turn_index;
        }
        if (func_800A0134(D_800814A8, actor) >= 0x81) {
            goto reset_turn_index;
        }
        if ((s16)func_8009A540(
                ((s32)(((S_801715F4_1 *)actor)->unk_2A.u << 16) >> 25) & 0xFFFF,
                ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
                (s16)(((S_801715F4_1 *)actor)->unk_88 - 0x20)) != 0) {
            goto clear_history;
        }
        if (turn_index == 0) {
            goto reset_turn_index;
        }

        dx = ((S_801715F4_2 *)position)->unk_24.at00.v;
        dx -= (target_x_wide = (u16)target_x);
        dx = abs(dx);
        if (dx >= 2) {
            goto call_path_held;
        }
        {
            s32 current_y;

            current_y = ((S_801715F4_2 *)position)->unk_24.at01.v;
            dy = current_y - (u16)target_y;
        }
        dy = abs(dy);
        if (dy < 2) {
            goto random_angle;
        }

call_path_held:
        ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
            ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v, (s16)target_x_wide, target_y,
            follow_context);
        goto reset_turn_index;
    }

    if (turn_index == 0) {
        goto call_obstacle;
    }
    dx = ((S_801715F4_2 *)position)->unk_24.at00.v;
    dx -= (target_x_wide = (u16)target_x);
    dx = abs(dx);
    if (dx >= 2) {
        goto call_path_direct;
    }
    {
        s32 current_y;

        current_y = ((S_801715F4_2 *)position)->unk_24.at01.v;
        dy = current_y - (u16)target_y;
    }
    dy = abs(dy);
    if (dy < 2) {
        goto random_angle;
    }

call_path_direct:
    ((S_801715F4_1 *)actor)->unk_2A.u = func_800A0818(
        ((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v, (s16)target_x_wide, target_y,
        (u8 *)move_state + 0x98);
    goto reset_turn_index;

random_angle:
    ((S_801715F4_1 *)actor)->unk_2A.u = (func_800A6D30() & 7) << 9;
    turn_index = 0;
    goto loop_setup;

call_obstacle:
    func_800A0E6C(position, ((S_801715F4_8 *)move_state)->unk_9C.s, actor,
                  (u8 *)move_state + 0x98);

reset_turn_index:
    turn_index = 0;

loop_setup:
    turn_table = (s16 *)&D_8006CD00;

loop:
    {
        s32 angle;

        angle = ((S_801715F4_1 *)actor)->unk_2A.s;
        if (((S_801715F4_8 *)move_state)->unk_98 & 2) {
            next_angle = angle - turn_table[turn_index];
        } else {
            next_angle = angle + turn_table[turn_index];
        }
        ASM_KEEP(angle);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    }

    if (func_8009A66C((s16)next_angle, position, actor, 0x20) > 0) {
        if (turn_index >= 3) {
            s32 turn_limit;

            turn_limit = limit_turns;
            ASM_KEEP(turn_limit);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (turn_limit != 0) {
                goto clear_history;
            }
        }

        ((S_801715F4_1 *)actor)->unk_2A.u = next_angle;
        ((S_801715F4_10 *)((u8 *)actor + (((S_801715F4_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
            ((S_801715F4_2 *)position)->unk_24.at00.v;
        ((S_801715F4_10 *)((u8 *)actor + (((S_801715F4_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
            ((S_801715F4_2 *)position)->unk_24.at01.v;
        ((S_801715F4_1 *)actor)->unk_71.u++;

        func_8009A3D0(((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
                      (((S_801715F4_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        table_offset = (((S_801715F4_1 *)actor)->unk_2A.u >> 8) & 0xE;
        {
            register u8 *x_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

            x_step = (u8 *)&D_8006CCD8 + table_offset;
            ASM_KEEP_NV(x_step);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            ((S_801715F4_2 *)position)->unk_24.at00.v += *x_step;
        }
        ((S_801715F4_2 *)position)->unk_24.at01.v +=
            *(u8 *)((u8 *)&D_8006CCE8 + table_offset);

        func_8009A21C(((S_801715F4_2 *)position)->unk_24.at00.v, ((S_801715F4_2 *)position)->unk_24.at01.v,
                      (((S_801715F4_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        goto after_loop;
    }

    if (turn_index == 0) {
        if (*(u16 *)&D_80082EA4 != ((S_801715F4_2 *)position)->unk_24.at00u.v) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            if ((s16)func_8009A180(
                    actor,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                goto end;
            }
        }
    }

    turn_index++;
    if (turn_index < 8) {
        goto loop;
    }

after_loop:
    if (turn_index >= 8) {
        ((S_801715F4_1 *)actor)->unk_71.u &= 0x7F;
        ((S_801715F4_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor);
        goto end;
    }

    ((S_801715F4_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_801715F4_8 *)move_state)->unk_9C.u = ((S_801715F4_2 *)position)->unk_26.u;
    ((S_801715F4_1 *)actor)->unk_6D.u--;
    {
        u8 *counter_state = (u8 *)&D_80083460;

        ((S_801715F4_9 *)counter_state)->unk_08++;
    }
    if (((S_801715F4_1 *)actor)->unk_6D.s != 0) {
        goto remaining_count;
    }

clear_history:
    ((S_801715F4_1 *)actor)->unk_71.u &= 0x7F;
    goto end;

remaining_count:
    turn_index = func_800BCB04((((S_801715F4_2 *)position)->unk_24.at00.v << 6) | 0x20,
                            (((S_801715F4_2 *)position)->unk_24.at01.v << 6) | 0x20,
                            (s16)(((S_801715F4_1 *)actor)->unk_88 - 0x20));
    if (turn_index < 0x200) {
        ((S_801715F4_1 *)actor)->unk_88 = turn_index;
    }
    goto end;

end:
    return;
}
