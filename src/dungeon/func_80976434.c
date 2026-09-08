#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80171C34_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_80171C34_0;   /* global in func_80171C34 */

typedef struct S_80171C34_1 {
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
} S_80171C34_1;   /* arg3 in func_80171C34 */

typedef struct S_80171C34_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_80171C34_2;   /* arg2 in func_80171C34 */

typedef struct S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80171C34_3_pre;   /* the 0x14 bytes before other in func_80171C34, addressed as other[-1] */

typedef struct S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80171C34_3;   /* other in func_80171C34 */


typedef struct S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_80171C34_5;   /* arg0 in func_80171C34 */

typedef struct S_80171C34_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_80171C34_6;   /* global_count in func_80171C34 */

typedef struct S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171C34_7;   /* ((S_80171C34_3_pre *)other)[-1].unk_00 in func_80171C34 */

typedef struct S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171C34_8;   /* (u8 *)arg3 + (((S_80171C34_1 *)arg3)->unk_71.u & 0x7F) in func_80171C34 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_8017237C(void *, void *, void *, void *);
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
extern s16 func_8009A8C0(s16, void *, void *, s32);
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

void func_80171C34(void *arg0_, void *arg1, void *arg2_, void *arg3_)
{
    register void *arg0 ASM_REG("$21") = arg0_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *arg2 ASM_REG("$19") = arg2_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *arg3 ASM_REG("$18") = arg3_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *global = (u8 *)&D_80083460;
    u16 global_flags = ((S_80171C34_0 *)global)->unk_02;
    s32 special_path = 0;
    s32 special_test;
    s32 flags;
    void *other;
    s32 trial;
    register s32 current_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 turn_flags;
    s16 i;
    s16 *turn_table;
    s32 dx;

    if (global_flags & 0x4000) {
        goto process_state;
    }
    if (((S_80171C34_1 *)arg3)->unk_71.s < 0) {
        goto check_active;
    }

process_state:
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if (((S_80171C34_1 *)arg3)->unk_12 >= 2) {
        goto reject_state;
    }
    if ((s16)func_8017237C(arg0, arg1, arg2, arg3) != 0) {
        goto accept_state;
    }

reject_state:
    func_800A9A0C(arg3);
    return;

accept_state:
    if (((S_80171C34_0 *)global)->unk_0C == arg3) {
        ((S_80171C34_1 *)arg3)->unk_46 = 0xC008;
    }
    return;

check_active:
    if (!(global_flags & 0x2000)) {
        return;
    }

active:
    func_800A19E4(arg2, arg3, 3, 6, (u8 *)arg0 + 0x9C);
    flags = ((S_80171C34_1 *)arg3)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            other = func_800A02AC(arg3, ((S_80171C34_2 *)arg2)->unk_24.at00.v,
                                  ((S_80171C34_2 *)arg2)->unk_24.at01.v);
            if (other != 0) {
                s16 result = func_800A0818(
                    ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                    ((S_80171C34_7 *)(((S_80171C34_3_pre *)other)[-1].unk_00))->unk_24,
                    ((S_80171C34_7 *)(((S_80171C34_3_pre *)other)[-1].unk_00))->unk_25,
                    (u8 *)arg0 + 0x98);
                ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                ((S_80171C34_1 *)arg3)->unk_2A.s = result;
                ((S_80171C34_1 *)arg3)->unk_71.u &= 0x7F;
                return;
            }
            if (((S_80171C34_1 *)arg3)->unk_14 & 0x80000000) {
                goto init_loop;
            }
            ((S_80171C34_1 *)arg3)->unk_14 |= 0x80000000;
            ((S_80171C34_1 *)arg3)->unk_2A.u +=
                (func_800A6D30() & 7) << 9;
            goto init_loop;
        }

        if (func_800A04F0(arg3, ((S_80171C34_2 *)arg2)->unk_24.at00.v,
                          ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                          ((S_80171C34_1 *)arg3)->unk_2A.s) == 0) {
            goto init_loop;
        }
        goto success;
    }

    if (flags & 0x2000) {
        if (((S_80171C34_1 *)arg3)->unk_46 & 0x8000) {
            goto init_loop;
        }
        if (flags & 0x20000) {
            s16 coordinate;
            s32 target_x;
            s32 target_y;
            u8 *buffer;
            {
                u8 *origin = D_80082E80_initial;
                s32 direction = ((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16;
                s32 table_index =
                    ((((S_80171C34_1 *)arg3)->unk_45 + ((s16)direction >> 9)) & 7) << 1;
                target_x = origin[0x24] +
                    *(u16 *)((u8 *)&D_8006CCD8 + table_index);
                target_y = origin[0x25] +
                    *(u16 *)((u8 *)&D_8006CCE8 + table_index);
            }

            if (((S_80171C34_2 *)arg2)->unk_24.at00.v == (u16)target_x &&
                ((S_80171C34_2 *)arg2)->unk_24.at01.v == (u16)target_y) {
                goto success;
            }

            buffer = (u8 *)arg0 + 0x98;
            coordinate = func_800A0818(
                ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                (s16)target_x, (s16)target_y, buffer);
            ((S_80171C34_1 *)arg3)->unk_2A.s = coordinate;
            if (func_8009A8C0(coordinate, arg2, arg3, 0x20) <= 0) {
                ((S_80171C34_1 *)arg3)->unk_2A.s = func_800A0818(
                    ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                    D_80082E80[0x24], D_80082E80[0x25], buffer);
            }
            if (func_8009FD7C(
                    ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                    D_80082E80[0x24], D_80082E80[0x25]) != 0) {
                special_path = 1;
            }
            goto init_loop;
        }
        goto direct_move;
    }

    if (((S_80171C34_2 *)arg2)->unk_26.s >= 0) {
        DungeonRecord *record = (DungeonRecord *)D_800E2970;
        if (record[((S_80171C34_2 *)arg2)->unk_26.s].flags & 2) {
            goto direct_move;
        }
    }
    if (((S_80171C34_1 *)arg3)->unk_46 & 0x8000) {
        goto init_loop;
    }

    other = func_800A04F0(arg3, ((S_80171C34_2 *)arg2)->unk_24.at00.v,
                          ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                          ((S_80171C34_1 *)arg3)->unk_2A.s);
    if (other != 0 &&
        (((S_80171C34_3 *)other)->unk_1C & 0x2000) &&
        (s16)func_800A0134(other, arg3) < 0x81) {
        if (func_8009A540(
                ((s16)((S_80171C34_1 *)arg3)->unk_2A.u >> 9) & 0xFFFF,
                ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                (s16)(((S_80171C34_1 *)arg3)->unk_88.u - 0x20)) != 0) {
            goto success;
        }
    }

    if (((S_80171C34_1 *)arg3)->unk_1C & 0x20000) {
        u8 *origin = D_80082E80;
        ((S_80171C34_1 *)arg3)->unk_2A.s = func_800A0818(
            ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
            origin[0x24], origin[0x25], (u8 *)arg0 + 0x98);
        if (func_8009FD7C(
                ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                origin[0x24], origin[0x25]) == 0) {
            goto init_loop;
        }
        if (func_800A0134(D_800814A8, arg3) >= 0x81) {
            goto init_loop;
        }
        if (func_8009A540(
                ((s16)((S_80171C34_1 *)arg3)->unk_2A.u >> 9) & 0xFFFF,
                ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
                (s16)(((S_80171C34_1 *)arg3)->unk_88.u - 0x20)) == 0) {
            goto init_loop;
        }
        goto success;
    }

direct_move:
    func_800A0E6C(arg2, ((S_80171C34_5 *)arg0)->unk_9C.s, arg3,
                  (u8 *)arg0 + 0x98);

init_loop:
    i = 0;
    turn_table = D_8006CD00;

loop_body:
    turn_flags = ((S_80171C34_5 *)arg0)->unk_98;
    ASM_KEEP(turn_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    current_angle = ((S_80171C34_1 *)arg3)->unk_2A.s;
    ASM_KEEP_NV(current_angle);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (turn_flags & 2) {
        trial = current_angle - turn_table[i];
    } else {
        trial = current_angle + turn_table[i];
    }

    if (func_8009A8C0(trial, arg2, arg3, 0x20) > 0) {
        if (i >= 3) {
            special_test = special_path;
            ASM_KEEP_NV(special_test);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (special_test != 0) {
                goto success;
            }
        }

        ((S_80171C34_1 *)arg3)->unk_2A.s = trial;
        ((S_80171C34_8 *)((u8 *)arg3 + (((S_80171C34_1 *)arg3)->unk_71.u & 0x7F)))->unk_74 =
            ((S_80171C34_2 *)arg2)->unk_24.at00.v;
        ((S_80171C34_8 *)((u8 *)arg3 + (((S_80171C34_1 *)arg3)->unk_71.u & 0x7F)))->unk_7C =
            ((S_80171C34_2 *)arg2)->unk_24.at01.v;
        ((S_80171C34_1 *)arg3)->unk_71.u++;

        func_8009A3D0(
            ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
            (((S_80171C34_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        {
            u8 *x_step;
            register s32 old_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

            dx = (((S_80171C34_1 *)arg3)->unk_2A.u >> 8) & 0xE;
            x_step = (u8 *)&D_8006CCD8 + dx;
            old_x = ((S_80171C34_2 *)arg2)->unk_24.at00.v;
            ((S_80171C34_2 *)arg2)->unk_24.at00.v = old_x + *x_step;
            ((S_80171C34_2 *)arg2)->unk_24.at01.v += *((u8 *)&D_8006CCE8 + dx);
        }

        func_8009A21C(
            ((S_80171C34_2 *)arg2)->unk_24.at00.v, ((S_80171C34_2 *)arg2)->unk_24.at01.v,
            (((S_80171C34_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        goto loop_test;
    }

    if (i == 0 &&
        *(u16 *)&D_80082EA4 != ((S_80171C34_2 *)arg2)->unk_24.at00u.v) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        if (func_8009A180(arg3,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
            return;
        }
    }

    i++;
    if (i < 8) {
        goto loop_body;
    }

loop_test:
    if (i >= 8) {
        ((S_80171C34_1 *)arg3)->unk_71.u &= 0x7F;
        ((S_80171C34_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A9A0C(arg3);
        return;
    }

    {
        u8 *global_count = (u8 *)&D_80083460;
        ((S_80171C34_1 *)arg3)->unk_46 &= 0x7FFF;
        ((S_80171C34_5 *)arg0)->unk_9C.u = ((S_80171C34_2 *)arg2)->unk_26.u;
        ((S_80171C34_1 *)arg3)->unk_6D.u--;
        ((S_80171C34_6 *)global_count)->unk_08++;
    }
    if (((S_80171C34_1 *)arg3)->unk_6D.s == 0) {
success:
        ((S_80171C34_1 *)arg3)->unk_71.u &= 0x7F;
        return;
    }

    i = func_800BCB04(
        (((S_80171C34_2 *)arg2)->unk_24.at00.v << 6) | 0x20,
        (((S_80171C34_2 *)arg2)->unk_24.at01.v << 6) | 0x20,
        (s16)(((S_80171C34_1 *)arg3)->unk_88.u - 0x20));
    if (i < 0x200) {
        ((S_80171C34_1 *)arg3)->unk_88.s = i;
    }
}
