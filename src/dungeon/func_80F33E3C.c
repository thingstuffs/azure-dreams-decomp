#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017163C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8017163C_0;   /* global in func_8017163C */

typedef struct S_8017163C_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8017163C_1;   /* arg3 in func_8017163C */

typedef struct S_8017163C_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8017163C_2;   /* arg2 in func_8017163C */

typedef struct S_8017163C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017163C_3_pre;   /* the 0x14 bytes before other in func_8017163C, addressed as other[-1] */

typedef struct S_8017163C_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8017163C_3;   /* other in func_8017163C */


typedef struct S_8017163C_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_8017163C_5;   /* arg0 in func_8017163C */

typedef struct S_8017163C_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8017163C_6;   /* global_count in func_8017163C */

typedef struct S_8017163C_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017163C_7;   /* ((S_8017163C_3_pre *)other)[-1].unk_00 in func_8017163C */

typedef struct S_8017163C_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017163C_8;   /* (u8 *)arg3 + (((S_8017163C_1 *)arg3)->unk_71.u & 0x7F) in func_8017163C */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80171DFC(void *, void *, void *, void *);
extern void func_800A9A0C(void *);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void *func_800A02AC(void *, u8, u8);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A6D30(void);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A0134(void *, void *);
extern s16 func_8009A540(s32, s32, s32, s16);
extern s16 func_8009FD7C(s32, s32, s32, s32);
extern void func_800A0E6C(void *, s8, void *, void *);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A21C(s32, s32, s32);
extern s16 func_8009A180(void *, void *);
extern s16 func_800BCB04(s32, s32, s16);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00[];
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_initial[] __asm__("D_80082E80");
extern u8 D_80082E80_fallback[] __asm__("D_80082E80");
extern u8 D_80082E80_check[] __asm__("D_80082E80");
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

/* Updates an actor's movement path, trying alternate directions around obstacles. */
void func_8017163C(void *move_ctx_in, void *action_ctx, void *position_in, void *actor_in)
{
    register void *move_ctx ASM_REG("$21") = move_ctx_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *position ASM_REG("$19") = position_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$18") = actor_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *dungeon_state = (u8 *)&D_80083460;
    u16 dungeon_flags = ((S_8017163C_0 *)dungeon_state)->unk_02;
    s32 near_target = 0;
    register s16 stop_turning;
    s32 actor_flags;
    void *target;
    s32 trial_angle;
    register s32 current_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 direction_offset;

    if (dungeon_flags & 0x4000) {
        goto process_state;
    }
    if (((S_8017163C_1 *)actor)->unk_71.s < 0) {
        goto check_active;
    }

process_state:
    ASM_KEEP(move_ctx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if (((S_8017163C_1 *)actor)->unk_12 >= 2) {
        goto reject_state;
    }
    if ((s16)func_80171DFC(move_ctx, action_ctx, position, actor) != 0) {
        goto accept_state;
    }

reject_state:
    func_800A9A0C(actor);
    return;

accept_state:
    if (((S_8017163C_0 *)dungeon_state)->unk_0C == actor) {
        ((S_8017163C_1 *)actor)->unk_46 = 0xC008;
    }
    return;

check_active:
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

active:
    func_800A19E4(position, actor, 3, 6, (u8 *)move_ctx + 0x9C);
    actor_flags = ((S_8017163C_1 *)actor)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target = func_800A02AC(actor, ((S_8017163C_2 *)position)->unk_24.at00.v,
                                  ((S_8017163C_2 *)position)->unk_24.at01.v);
            if (target != 0) {
                s16 target_angle = func_800A0818(
                    ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                    ((S_8017163C_7 *)(((S_8017163C_3_pre *)target)[-1].unk_00))->unk_24,
                    ((S_8017163C_7 *)(((S_8017163C_3_pre *)target)[-1].unk_00))->unk_25,
                    (u8 *)move_ctx + 0x98);
                ASM_KEEP(move_ctx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ((S_8017163C_1 *)actor)->unk_2A.s = target_angle;
                ((S_8017163C_1 *)actor)->unk_71.u &= 0x7F;
                return;
            }
            if (((S_8017163C_1 *)actor)->unk_14 & 0x80000000) {
                goto init_loop;
            }
            ((S_8017163C_1 *)actor)->unk_14 |= 0x80000000;
            ((S_8017163C_1 *)actor)->unk_2A.u +=
                (func_800A6D30() & 7) << 9;
            goto init_loop;
        }

        if (func_800A04F0(actor, ((S_8017163C_2 *)position)->unk_24.at00.v,
                          ((S_8017163C_2 *)position)->unk_24.at01.v,
                          ((S_8017163C_1 *)actor)->unk_2A.s) == 0) {
            goto init_loop;
        }
        goto success;
    }

    if (actor_flags & 0x2000) {
        if (((S_8017163C_1 *)actor)->unk_46 & 0x8000) {
            goto init_loop;
        }
        if (actor_flags & 0x20000) {
            s16 target_angle;
            s32 target_x;
            s32 target_y;
            u8 *move_flags;
            {
                u8 *target_position = D_80082E80_initial;
                s32 target_heading = ((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16;
                s32 table_index =
                    ((((S_8017163C_1 *)actor)->unk_45 + ((s16)target_heading >> 9)) & 7) << 1;
                target_x = target_position[0x24] +
                    *(u16 *)((u8 *)&D_8006CCD8 + table_index);
                target_y = target_position[0x25] +
                    *(u16 *)((u8 *)&D_8006CCE8 + table_index);
            }

            if (((S_8017163C_2 *)position)->unk_24.at00.v == (u16)target_x &&
                ((S_8017163C_2 *)position)->unk_24.at01.v == (u16)target_y) {
                goto success;
            }

            move_flags = (u8 *)move_ctx + 0x98;
            target_angle = func_800A0818(
                ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                (s16)target_x, (s16)target_y, move_flags);
            ((S_8017163C_1 *)actor)->unk_2A.s = target_angle;
            if (func_8009A66C(target_angle, position, actor, 0x20) <= 0) {
                ((S_8017163C_1 *)actor)->unk_2A.s = func_800A0818(
                    ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                    D_80082E80[0x24], D_80082E80[0x25], move_flags);
            }
            if (func_8009FD7C(
                    ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                    D_80082E80[0x24], D_80082E80[0x25]) != 0) {
                near_target = 1;
            }
            goto init_loop;
        }
        goto direct_move;
    }

    if (((S_8017163C_2 *)position)->unk_26.s >= 0) {
        DungeonRecord *room_records = (DungeonRecord *)D_800E2970;
        if (room_records[((S_8017163C_2 *)position)->unk_26.s].flags & 2) {
            goto direct_move;
        }
    }
    if (((S_8017163C_1 *)actor)->unk_46 & 0x8000) {
        goto init_loop;
    }
    if (((S_8017163C_5 *)move_ctx)->unk_98 & 0x8000) {
        goto init_loop;
    }

    target = func_800A04F0(actor, ((S_8017163C_2 *)position)->unk_24.at00.v,
                          ((S_8017163C_2 *)position)->unk_24.at01.v,
                          ((S_8017163C_1 *)actor)->unk_2A.s);
    if (target != 0 &&
        (((S_8017163C_3 *)target)->unk_1C & 0x2000) &&
        (s16)func_800A0134(target, actor) < 0x81) {
        if (func_8009A540(
                ((s16)((S_8017163C_1 *)actor)->unk_2A.u >> 9) & 0xFFFF,
                ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                (s16)(((S_8017163C_1 *)actor)->unk_88.u - 0x20)) != 0) {
            goto success;
        }
    }

    if (((S_8017163C_1 *)actor)->unk_1C & 0x20000) {
        u8 *target_position = D_80082E80;
        ((S_8017163C_1 *)actor)->unk_2A.s = func_800A0818(
            ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
            target_position[0x24], target_position[0x25], (u8 *)move_ctx + 0x98);
        if (func_8009FD7C(
                ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                target_position[0x24], target_position[0x25]) == 0) {
            goto init_loop;
        }
        if ((s16)func_800A0134(D_800814A8, actor) >= 0x81) {
            goto init_loop;
        }
        if (func_8009A540(
                ((s16)((S_8017163C_1 *)actor)->unk_2A.u >> 9) & 0xFFFF,
                ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
                (s16)(((S_8017163C_1 *)actor)->unk_88.u - 0x20)) == 0) {
            goto init_loop;
        }
        goto success;
    }

direct_move:
    func_800A0E6C(position, ((S_8017163C_5 *)move_ctx)->unk_9C.s, actor,
                  (u8 *)move_ctx + 0x98);

init_loop:
    turn_index = 0;
    turn_table = D_8006CD00;

loop_body:
    turn_flags = ((S_8017163C_5 *)move_ctx)->unk_98;
    current_angle = ((S_8017163C_1 *)actor)->unk_2A.s;
    if (turn_flags & 2) {
        trial_angle = current_angle - turn_table[turn_index];
    } else {
        trial_angle = current_angle + turn_table[turn_index];
    }

    if (func_8009A66C(trial_angle, position, actor, 0x20) > 0) {
        if (turn_index >= 3) {
            stop_turning = near_target;
            if (stop_turning != 0) {
                goto success;
            }
        }

        ((S_8017163C_1 *)actor)->unk_2A.s = trial_angle;
        ((S_8017163C_8 *)((u8 *)actor + (((S_8017163C_1 *)actor)->unk_71.u & 0x7F)))->unk_74 =
            ((S_8017163C_2 *)position)->unk_24.at00.v;
        ((S_8017163C_8 *)((u8 *)actor + (((S_8017163C_1 *)actor)->unk_71.u & 0x7F)))->unk_7C =
            ((S_8017163C_2 *)position)->unk_24.at01.v;
        ((S_8017163C_1 *)actor)->unk_71.u++;

        func_8009A3D0(
            ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
            (((S_8017163C_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        {
            register u8 old_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            u8 old_y;

            old_x = ((S_8017163C_2 *)position)->unk_24.at00.v;
            direction_offset = (((S_8017163C_1 *)actor)->unk_2A.u >> 8) & 0xE;
            ((S_8017163C_2 *)position)->unk_24.at00.v = old_x +
                *((u8 *)&D_8006CCD8 + direction_offset);
            old_y = ((S_8017163C_2 *)position)->unk_24.at01.v;
            ((S_8017163C_2 *)position)->unk_24.at01.v = old_y +
                *((u8 *)&D_8006CCE8 + direction_offset);
        }

        func_8009A21C(
            ((S_8017163C_2 *)position)->unk_24.at00.v, ((S_8017163C_2 *)position)->unk_24.at01.v,
            (((S_8017163C_1 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        goto loop_test;
    }

    if (turn_index == 0 &&
        *(u16 *)&D_80082EA4 != ((S_8017163C_2 *)position)->unk_24.at00u.v) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        if (func_8009A180(actor,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
            return;
        }
    }

    turn_index++;
    if (turn_index < 8) {
        goto loop_body;
    }

loop_test:
    if (turn_index >= 8) {
        ((S_8017163C_1 *)actor)->unk_71.u &= 0x7F;
        ((S_8017163C_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor);
        return;
    }

    {
        u8 *dungeon_counters = (u8 *)&D_80083460;
        ((S_8017163C_1 *)actor)->unk_46 &= 0x7FFF;
        ((S_8017163C_5 *)move_ctx)->unk_9C.u = ((S_8017163C_2 *)position)->unk_26.u;
        ((S_8017163C_1 *)actor)->unk_6D.u--;
        ((S_8017163C_6 *)dungeon_counters)->unk_08++;
    }
    if (((S_8017163C_1 *)actor)->unk_6D.s == 0) {
success:
        ((S_8017163C_1 *)actor)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = func_800BCB04(
        (((S_8017163C_2 *)position)->unk_24.at00.v << 6) | 0x20,
        (((S_8017163C_2 *)position)->unk_24.at01.v << 6) | 0x20,
        (s16)(((S_8017163C_1 *)actor)->unk_88.u - 0x20));
    if (turn_index < 0x200) {
        ((S_8017163C_1 *)actor)->unk_88.s = turn_index;
    }
}
