#include "common.h"

typedef struct S_8127C3E0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8127C3E0_0;   /* global in func_8127C3E0 */

typedef struct S_8127C3E0_1 {
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
} S_8127C3E0_1;   /* arg3 in func_8127C3E0 */

typedef struct S_8127C3E0_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8127C3E0_2;   /* arg2 in func_8127C3E0 */

typedef struct S_8127C3E0_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8127C3E0_3_pre;   /* the 0x14 bytes before other in func_8127C3E0, addressed as other[-1] */

typedef struct S_8127C3E0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8127C3E0_3;   /* other in func_8127C3E0 */

typedef struct S_8127C3E0_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    void * unk_58;
} S_8127C3E0_4;   /* D_800803DC in func_8127C3E0 */

typedef struct S_8127C3E0_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_8127C3E0_5;   /* arg0 in func_8127C3E0 */

typedef struct S_8127C3E0_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8127C3E0_6;   /* global_count in func_8127C3E0 */

typedef struct S_8127C3E0_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8127C3E0_7;   /* ((S_8127C3E0_3_pre *)other)[-1].unk_00 in func_8127C3E0 */

typedef struct S_8127C3E0_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8127C3E0_8;   /* (u8 *)arg3 + (((S_8127C3E0_1 *)arg3)->unk_71.u & 0x7F) in func_8127C3E0 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80171328(void *, void *, void *, void *);
extern void func_800A86C4(void *);
extern void func_800A06B4(void *, void *, s32, s32, void *);
extern void *func_8009F09C(void *, u8, u8);
extern s16 func_8009F608(s32, s32, s32, s32, void *);
extern s32 func_800A59E8(void);
extern void *func_8009F2E0(void *, u8, u8, s16);
extern s16 func_8009EF24(void *, void *);
extern s16 func_80099330(s32, s32, s32, s16);
extern s16 func_8009EB6C(s32, s32, s32, s32);
extern void func_8009FB34(void *, s8, void *, void *);
extern s16 func_800996B0(s16, void *, void *, s32);
extern void func_800991C0(s32, s32, s32);
extern void func_8009900C(s32, s32, s32);
extern s16 func_80098F70(void *, void *);
extern s16 func_800BB784(s32, s32, s16);

extern s8 D_8006BDA8;
extern s8 D_8006BDB8;
extern s16 D_8006BDD0[];
extern void *D_800803DC;
extern u8 D_80081490[];
extern u8 D_80082E80_initial[] __asm__("D_80081490");
extern u8 D_80082E80_fallback[] __asm__("D_80081490");
extern u8 D_80082E80_check[] __asm__("D_80081490");
extern s8 D_800814B4;
extern s32 D_80085990;
extern s8 D_800E1D50[];

void func_8127C3E0(void *arg0_, void *arg1, void *arg2_, void *arg3_)
{
    register void *arg0 ASM_REG("$21") = arg0_;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *arg2 ASM_REG("$19") = arg2_;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *arg3 ASM_REG("$18") = arg3_;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *global = (u8 *)&D_80085990;
    u16 global_flags = ((S_8127C3E0_0 *)global)->unk_02;
    s32 special_path = 0;
    register s32 special_test;
    s32 flags;
    void *other;
    s32 trial;
    register s32 current_angle ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u16 turn_flags;
    s16 i;
    s16 *turn_table;
    s32 dx;

    if (global_flags & 0x4000) {
        goto process_state;
    }
    if (((S_8127C3E0_1 *)arg3)->unk_71.s < 0) {
        goto check_active;
    }

process_state:
    ASM_KEEP(arg0);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(arg2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(arg3);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    if (((S_8127C3E0_1 *)arg3)->unk_12 >= 2) {
        goto reject_state;
    }
    if ((s16)func_80171328(arg0, arg1, arg2, arg3) != 0) {
        goto accept_state;
    }

reject_state:
    func_800A86C4(arg3);
    return;

accept_state:
    if (((S_8127C3E0_0 *)global)->unk_0C == arg3) {
        ((S_8127C3E0_1 *)arg3)->unk_46 = 0xC008;
    }
    return;

check_active:
    if (!(global_flags & 0x2000)) {
        return;
    }

active:
    func_800A06B4(arg2, arg3, 3, 6, (u8 *)arg0 + 0x9C);
    flags = ((S_8127C3E0_1 *)arg3)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            other = func_8009F09C(arg3, ((S_8127C3E0_2 *)arg2)->unk_24.at00.v,
                                  ((S_8127C3E0_2 *)arg2)->unk_24.at01.v);
            if (other != 0) {
                s16 result = func_8009F608(
                    ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                    ((S_8127C3E0_7 *)(((S_8127C3E0_3_pre *)other)[-1].unk_00))->unk_24,
                    ((S_8127C3E0_7 *)(((S_8127C3E0_3_pre *)other)[-1].unk_00))->unk_25,
                    (u8 *)arg0 + 0x98);
                ASM_KEEP(arg0);   /* MATCH pin: retail basic-block layout depends on it */
                ((S_8127C3E0_1 *)arg3)->unk_2A.s = result;
                ((S_8127C3E0_1 *)arg3)->unk_71.u &= 0x7F;
                return;
            }
            if (((S_8127C3E0_1 *)arg3)->unk_14 & 0x80000000) {
                goto init_loop;
            }
            ((S_8127C3E0_1 *)arg3)->unk_14 |= 0x80000000;
            ((S_8127C3E0_1 *)arg3)->unk_2A.u +=
                (func_800A59E8() & 7) << 9;
            goto init_loop;
        }

        if (func_8009F2E0(arg3, ((S_8127C3E0_2 *)arg2)->unk_24.at00.v,
                          ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                          ((S_8127C3E0_1 *)arg3)->unk_2A.s) == 0) {
            goto init_loop;
        }
        goto success;
    }

    if (flags & 0x2000) {
        if (((S_8127C3E0_1 *)arg3)->unk_46 & 0x8000) {
            goto init_loop;
        }
        if (flags & 0x20000) {
            s16 coordinate;
            s32 target_x;
            s32 target_y;
            u8 *buffer;
            {
                u8 *origin = D_80082E80_initial;
                s32 direction = ((S_8127C3E0_4 *)D_800803DC)->unk_2A;
                s32 table_index =
                    ((((S_8127C3E0_1 *)arg3)->unk_45 + ((s16)direction >> 9)) & 7) << 1;
                target_x = origin[0x24] +
                    *(u16 *)((u8 *)&D_8006BDA8 + table_index);
                target_y = origin[0x25] +
                    *(u16 *)((u8 *)&D_8006BDB8 + table_index);
            }

            if (((S_8127C3E0_2 *)arg2)->unk_24.at00.v == (u16)target_x &&
                ((S_8127C3E0_2 *)arg2)->unk_24.at01.v == (u16)target_y) {
                goto success;
            }

            buffer = (u8 *)arg0 + 0x98;
            coordinate = func_8009F608(
                ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                (s16)target_x, (s16)target_y, buffer);
            ((S_8127C3E0_1 *)arg3)->unk_2A.s = coordinate;
            if (func_800996B0(coordinate, arg2, arg3, 0x20) <= 0) {
                ((S_8127C3E0_1 *)arg3)->unk_2A.s = func_8009F608(
                    ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                    D_80081490[0x24], D_80081490[0x25], buffer);
            }
            if (func_8009EB6C(
                    ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                    D_80081490[0x24], D_80081490[0x25]) != 0) {
                special_path = 1;
            }
            goto init_loop;
        }
        goto direct_move;
    }

    if (((S_8127C3E0_2 *)arg2)->unk_26.s >= 0) {
        DungeonRecord *record = (DungeonRecord *)D_800E1D50;
        if (record[((S_8127C3E0_2 *)arg2)->unk_26.s].flags & 2) {
            goto direct_move;
        }
    }
    if (((S_8127C3E0_1 *)arg3)->unk_46 & 0x8000) {
        goto init_loop;
    }

    other = func_8009F2E0(arg3, ((S_8127C3E0_2 *)arg2)->unk_24.at00.v,
                          ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                          ((S_8127C3E0_1 *)arg3)->unk_2A.s);
    if (other != 0 &&
        (((S_8127C3E0_3 *)other)->unk_1C & 0x2000) &&
        (s16)func_8009EF24(other, arg3) < 0x81) {
        if (func_80099330(
                ((s16)((S_8127C3E0_1 *)arg3)->unk_2A.u >> 9) & 0xFFFF,
                ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                (s16)(((S_8127C3E0_1 *)arg3)->unk_88.u - 0x20)) != 0) {
            goto success;
        }
    }

    if (((S_8127C3E0_1 *)arg3)->unk_1C & 0x20000) {
        u8 *origin = D_80081490;
        ((S_8127C3E0_1 *)arg3)->unk_2A.s = func_8009F608(
            ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
            origin[0x24], origin[0x25], (u8 *)arg0 + 0x98);
        if (func_8009EB6C(
                ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                origin[0x24], origin[0x25]) == 0) {
            goto init_loop;
        }
        if ((s16)func_8009EF24(D_800803DC, arg3) >= 0x81) {
            goto init_loop;
        }
        if (func_80099330(
                ((s16)((S_8127C3E0_1 *)arg3)->unk_2A.u >> 9) & 0xFFFF,
                ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
                (s16)(((S_8127C3E0_1 *)arg3)->unk_88.u - 0x20)) == 0) {
            goto init_loop;
        }
        goto success;
    }

direct_move:
    func_8009FB34(arg2, ((S_8127C3E0_5 *)arg0)->unk_9C.s, arg3,
                  (u8 *)arg0 + 0x98);

init_loop:
    i = 0;
    turn_table = D_8006BDD0;

loop_body:
    turn_flags = ((S_8127C3E0_5 *)arg0)->unk_98;
    ASM_KEEP(turn_flags);   /* MATCH pin: retail delay-slot fill depends on it */
    current_angle = ((S_8127C3E0_1 *)arg3)->unk_2A.s;
    ASM_KEEP_NV(current_angle);   /* MATCH pin: retail delay-slot fill depends on it */
    if (turn_flags & 2) {
        trial = current_angle - turn_table[i];
    } else {
        trial = current_angle + turn_table[i];
    }

    if (func_800996B0(trial, arg2, arg3, 0x20) > 0) {
        if (i >= 3) {
            special_test = special_path;
            ASM_KEEP_NV(special_test);   /* MATCH pin: load-bearing for the whole function shape */
            if (special_test != 0) {
                goto success;
            }
        }

        ((S_8127C3E0_1 *)arg3)->unk_2A.s = trial;
        ((S_8127C3E0_8 *)((u8 *)arg3 + (((S_8127C3E0_1 *)arg3)->unk_71.u & 0x7F)))->unk_74 =
            ((S_8127C3E0_2 *)arg2)->unk_24.at00.v;
        ((S_8127C3E0_8 *)((u8 *)arg3 + (((S_8127C3E0_1 *)arg3)->unk_71.u & 0x7F)))->unk_7C =
            ((S_8127C3E0_2 *)arg2)->unk_24.at01.v;
        ((S_8127C3E0_1 *)arg3)->unk_71.u++;

        func_800991C0(
            ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
            (((S_8127C3E0_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        {
            register u8 old_x ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
            u8 old_y;

            old_x = ((S_8127C3E0_2 *)arg2)->unk_24.at00.v;
            dx = (((S_8127C3E0_1 *)arg3)->unk_2A.u >> 8) & 0xE;
            ((S_8127C3E0_2 *)arg2)->unk_24.at00.v = old_x +
                *((u8 *)&D_8006BDA8 + dx);
            old_y = ((S_8127C3E0_2 *)arg2)->unk_24.at01.v;
            ((S_8127C3E0_2 *)arg2)->unk_24.at01.v = old_y +
                *((u8 *)&D_8006BDB8 + dx);
        }

        func_8009900C(
            ((S_8127C3E0_2 *)arg2)->unk_24.at00.v, ((S_8127C3E0_2 *)arg2)->unk_24.at01.v,
            (((S_8127C3E0_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        goto loop_test;
    }

    if (i == 0 &&
        *(u16 *)&D_800814B4 != ((S_8127C3E0_2 *)arg2)->unk_24.at00u.v) {
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        if (func_80098F70(arg3,
                (u8 *)((S_8127C3E0_4 *)D_800803DC)->unk_58 + 0x20) != 0) {
            return;
        }
    }

    i++;
    if (i < 8) {
        goto loop_body;
    }

loop_test:
    if (i >= 8) {
        ((S_8127C3E0_1 *)arg3)->unk_71.u &= 0x7F;
        ((S_8127C3E0_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A86C4(arg3);
        return;
    }

    {
        u8 *global_count = (u8 *)&D_80085990;
        ((S_8127C3E0_1 *)arg3)->unk_46 &= 0x7FFF;
        ((S_8127C3E0_5 *)arg0)->unk_9C.u = ((S_8127C3E0_2 *)arg2)->unk_26.u;
        ((S_8127C3E0_1 *)arg3)->unk_6D.u--;
        ((S_8127C3E0_6 *)global_count)->unk_08++;
    }
    if (((S_8127C3E0_1 *)arg3)->unk_6D.s == 0) {
success:
        ((S_8127C3E0_1 *)arg3)->unk_71.u &= 0x7F;
        return;
    }

    i = func_800BB784(
        (((S_8127C3E0_2 *)arg2)->unk_24.at00.v << 6) | 0x20,
        (((S_8127C3E0_2 *)arg2)->unk_24.at01.v << 6) | 0x20,
        (s16)(((S_8127C3E0_1 *)arg3)->unk_88.u - 0x20));
    if (i < 0x200) {
        ((S_8127C3E0_1 *)arg3)->unk_88.s = i;
    }
}
