#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80171E38(void *, void *, void *, void *);
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

void func_801716A4(void *arg0_, void *arg1, void *arg2_, void *arg3_)
{
    register void *arg0 ASM_REG("$21") = arg0_;
    register void *arg2 ASM_REG("$19") = arg2_;
    register void *arg3 ASM_REG("$18") = arg3_;
    u8 *global = (u8 *)&D_80083460;
    u16 global_flags = FIELD(global, u16, 2);
    s32 special_path = 0;
    register s32 special_test ASM_REG("$2");
    s32 flags;
    void *other;
    s32 trial;
    register s32 current_angle ASM_REG("$3");
    u16 turn_flags;
    s16 i;
    s16 *turn_table;
    s32 dx;

    if (global_flags & 0x4000) {
        goto process_state;
    }
    if (FIELD(arg3, s8, 0x71) < 0) {
        goto check_active;
    }

process_state:
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    if (FIELD(arg3, u8, 0x12) >= 2) {
        goto reject_state;
    }
    if ((s16)func_80171E38(arg0, arg1, arg2, arg3) != 0) {
        goto accept_state;
    }

reject_state:
    func_800A9A0C(arg3);
    return;

accept_state:
    if (FIELD(global, void *, 0xC) == arg3) {
        FIELD(arg3, u16, 0x46) = 0xC008;
    }
    return;

check_active:
    if (!(global_flags & 0x2000)) {
        return;
    }

active:
    func_800A19E4(arg2, arg3, 2, 4, (u8 *)arg0 + 0x9C);
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x410) {
        if (flags & 0x400) {
            other = func_800A02AC(arg3, FIELD(arg2, u8, 0x24),
                                  FIELD(arg2, u8, 0x25));
            if (other != 0) {
                s16 result = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    FIELD(FIELD(other, void *, -0x14), u8, 0x24),
                    FIELD(FIELD(other, void *, -0x14), u8, 0x25),
                    (u8 *)arg0 + 0x98);
                ASM_KEEP(arg0);
                FIELD(arg3, s16, 0x2A) = result;
                FIELD(arg3, u8, 0x71) &= 0x7F;
                return;
            }
            if (FIELD(arg3, s32, 0x14) & 0x80000000) {
                goto init_loop;
            }
            FIELD(arg3, s32, 0x14) |= 0x80000000;
            FIELD(arg3, u16, 0x2A) +=
                (func_800A6D30() & 7) << 9;
            goto init_loop;
        }

        if (func_800A04F0(arg3, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25),
                          FIELD(arg3, s16, 0x2A)) == 0) {
            goto init_loop;
        }
        goto success;
    }

    if (flags & 0x2000) {
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            goto init_loop;
        }
        if (flags & 0x20000) {
            s16 coordinate;
            s32 target_x;
            s32 target_y;
            u8 *buffer;
            {
                u8 *origin = D_80082E80_initial;
                s32 direction = FIELD(D_800814A8, u16, 0x2A);
                s32 table_index =
                    ((FIELD(arg3, u8, 0x45) + ((s16)direction >> 9)) & 7) << 1;
                target_x = origin[0x24] +
                    *(u16 *)((u8 *)&D_8006CCD8 + table_index);
                target_y = origin[0x25] +
                    *(u16 *)((u8 *)&D_8006CCE8 + table_index);
            }

            if (FIELD(arg2, u8, 0x24) == (u16)target_x &&
                FIELD(arg2, u8, 0x25) == (u16)target_y) {
                goto success;
            }

            buffer = (u8 *)arg0 + 0x98;
            coordinate = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                (s16)target_x, (s16)target_y, buffer);
            FIELD(arg3, s16, 0x2A) = coordinate;
            if (func_8009A66C(coordinate, arg2, arg3, 0x20) <= 0) {
                FIELD(arg3, s16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    D_80082E80[0x24], D_80082E80[0x25], buffer);
            }
            if (func_8009FD7C(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    D_80082E80[0x24], D_80082E80[0x25]) != 0) {
                special_path = 1;
            }
            goto init_loop;
        }
        goto direct_move;
    }

    if (FIELD(arg2, s8, 0x26) >= 0) {
        DungeonRecord *record = (DungeonRecord *)D_800E2970;
        if (record[FIELD(arg2, s8, 0x26)].flags & 2) {
            goto direct_move;
        }
    }
    if (FIELD(arg3, u16, 0x46) & 0x8000) {
        goto init_loop;
    }

    other = func_800A04F0(arg3, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25),
                          FIELD(arg3, s16, 0x2A));
    if (other != 0 &&
        (FIELD(other, s32, 0x1C) & 0x2000) &&
        (s16)func_800A0134(other, arg3) < 0x81) {
        if (func_8009A540(
                ((s16)FIELD(arg3, u16, 0x2A) >> 9) & 0xFFFF,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                (s16)(FIELD(arg3, u16, 0x88) - 0x20)) != 0) {
            goto success;
        }
    }

    if (FIELD(arg3, s32, 0x1C) & 0x20000) {
        u8 *origin = D_80082E80;
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            origin[0x24], origin[0x25], (u8 *)arg0 + 0x98);
        if (func_8009FD7C(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                origin[0x24], origin[0x25]) == 0) {
            goto init_loop;
        }
        if (func_8009A540(
                ((s16)FIELD(arg3, u16, 0x2A) >> 9) & 0xFFFF,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                (s16)(FIELD(arg3, u16, 0x88) - 0x20)) == 0) {
            goto init_loop;
        }
        goto success;
    }

direct_move:
    func_800A0E6C(arg2, FIELD(arg0, s8, 0x9C), arg3,
                  (u8 *)arg0 + 0x98);

init_loop:
    i = 0;
    turn_table = D_8006CD00;

loop_body:
    turn_flags = FIELD(arg0, u16, 0x98);
    ASM_KEEP(turn_flags);
    current_angle = FIELD(arg3, s16, 0x2A);
    ASM_KEEP_NV(current_angle);
    if (turn_flags & 2) {
        trial = current_angle - turn_table[i];
    } else {
        trial = current_angle + turn_table[i];
    }

    if (func_8009A66C(trial, arg2, arg3, 0x20) > 0) {
        if (i >= 3) {
            special_test = special_path;
            ASM_KEEP_NV(special_test);
            if (special_test != 0) {
                goto success;
            }
        }

        FIELD(arg3, s16, 0x2A) = trial;
        FIELD((u8 *)arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x74) =
            FIELD(arg2, u8, 0x24);
        FIELD((u8 *)arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x7C) =
            FIELD(arg2, u8, 0x25);
        FIELD(arg3, u8, 0x71)++;

        func_8009A3D0(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);

        {
            register u8 old_x ASM_REG("$2");
            u8 old_y;

            old_x = FIELD(arg2, u8, 0x24);
            ASM_KEEP_NV(old_x);
            dx = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
            FIELD(arg2, u8, 0x24) = old_x +
                *((u8 *)&D_8006CCD8 + dx);
            old_y = FIELD(arg2, u8, 0x25);
            FIELD(arg2, u8, 0x25) = old_y +
                *((u8 *)&D_8006CCE8 + dx);
        }

        func_8009A21C(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        goto loop_test;
    }

    if (i == 0 &&
        *(u16 *)&D_80082EA4 != FIELD(arg2, u16, 0x24)) {
        ASM_SCHED_BARRIER();
        if (func_8009A180(arg3,
                (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
            return;
        }
    }

    i++;
    if (i < 8) {
        goto loop_body;
    }

loop_test:
    if (i >= 8) {
        FIELD(arg3, u8, 0x71) &= 0x7F;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A9A0C(arg3);
        return;
    }

    {
        u8 *global_count = (u8 *)&D_80083460;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        FIELD(arg0, u8, 0x9C) = FIELD(arg2, u8, 0x26);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(global_count, u16, 8)++;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
success:
        FIELD(arg3, u8, 0x71) &= 0x7F;
        return;
    }

    i = func_800BCB04(
        (FIELD(arg2, u8, 0x24) << 6) | 0x20,
        (FIELD(arg2, u8, 0x25) << 6) | 0x20,
        (s16)(FIELD(arg3, u16, 0x88) - 0x20));
    if (i < 0x200) {
        FIELD(arg3, s16, 0x88) = i;
    }
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
}
