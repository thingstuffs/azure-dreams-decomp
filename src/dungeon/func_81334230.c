#include "common.h"
#include "records/Rec_D_800814A8.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8016B230_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8016B230_0;   /* state in func_8016B230 */

typedef struct S_8016B230_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
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
} S_8016B230_1;   /* arg3 in func_8016B230 */

typedef struct S_8016B230_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8016B230_2;   /* arg2 in func_8016B230 */

typedef struct S_8016B230_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_8016B230_3_pre;   /* the 0x14 bytes before found in func_8016B230, addressed as found[-1] */

typedef struct S_8016B230_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8016B230_3;   /* found in func_8016B230 */

typedef struct S_8016B230_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_4;   /* object in func_8016B230 */

typedef struct S_8016B230_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
    u8 pad_9D[0x12];
    u8 unk_AF;
} S_8016B230_5;   /* arg0 in func_8016B230 */


typedef struct S_8016B230_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_7;   /* target in func_8016B230 */

typedef struct S_8016B230_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_8;   /* retry_target in func_8016B230 */

typedef struct S_8016B230_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B230_9;   /* check_target in func_8016B230 */

typedef struct S_8016B230_10 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B230_10;   /* kind_table + kind * 0x14 in func_8016B230 */

typedef struct S_8016B230_11 {
    u16 unk_00;
} S_8016B230_11;   /* &D_80082EA4 in func_8016B230 */

typedef struct S_8016B230_12 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016B230_12;   /* loop_state in func_8016B230 */

typedef struct S_8016B230_13 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016B230_13;   /* arg3 + (((S_8016B230_1 *)arg3)->unk_71.u & 0x7F) in func_8016B230 */



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
extern s32 func_8016B954();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

void func_8016B230(u8 *in0, void *arg1, u8 *in2, u8 *in3) {
    register u8 *arg0 ASM_REG("$21") = in0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register u8 *arg2 ASM_REG("$20") = in2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *arg3 ASM_REG("$18") = in3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 enabled ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 i ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s16 *delta;
    register u8 *x_table;
    u8 *state;
    u8 *loop_state;
    u32 flags;
    u32 attr;
    s32 ret;
    register s32 direction_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 loop_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 step;
    s32 base_wide;
    s16 move_angle;
    u8 call_x;
    u8 call_y;
    void *found;
    u8 *object;

    state = (u8 *)&D_80083460;
    do { flags = ((S_8016B230_0 *)state)->unk_02; } while (0);
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    enabled = 0;

    if ((flags & 0x4000) || (((S_8016B230_1 *)arg3)->unk_71.s >= 0)) {
        if ((((S_8016B230_1 *)arg3)->unk_12 >= 2) ||
            ((func_8016B954(arg0, arg1, arg2, arg3) << 16) == 0)) {
            func_800A9A0C(arg3);
            goto end;
        }
        if (((S_8016B230_0 *)state)->unk_0C != arg3) {
            goto end;
        }
        ((S_8016B230_1 *)arg3)->unk_46 = 0xC008;
        goto end;
    }
    if (!(flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
    attr = ((S_8016B230_1 *)arg3)->unk_1C;
    if (attr & 0x410) {
        if (attr & 0x400) {
            found = func_800A02AC(arg3, ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v);
            if (found != NULL) {
                object = ((S_8016B230_3_pre *)found)[-1].unk_00;
                ((S_8016B230_1 *)arg3)->unk_2A.u = func_800A0818(
                    ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                    ((S_8016B230_4 *)object)->unk_24, ((S_8016B230_4 *)object)->unk_25, arg0 + 0x98);
                ((S_8016B230_1 *)arg3)->unk_71.u &= 0x7F;
                goto end;
            }
            {
                register s32 object_status ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                object_status = ((S_8016B230_1 *)arg3)->unk_14;
                if (object_status >= 0) {
                    ((S_8016B230_1 *)arg3)->unk_14 = object_status | 0x80000000;
                    ret = func_800A6D30();
                    ((S_8016B230_1 *)arg3)->unk_2A.u += (ret & 7) << 9;
                }
            }
            goto init_loop;
        }
        found = func_800A04F0(arg3, ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                              ((S_8016B230_1 *)arg3)->unk_2A.s);
        i = 0;
        if (found == NULL) {
            goto setup_loop;
        }
        goto clear_history;
    }

    if (((S_8016B230_5 *)arg0)->unk_AF) {
        if (((S_8016B230_1 *)arg3)->unk_46 & 0x8000) {
            i = 0;
            goto setup_loop;
        }
        if (attr & 0x20000) {
            s32 direction;
            s16 target_x;
            s32 target_y;
            s16 new_angle;
            u8 *target;

            target = (u8 *)&D_80082EA4 - 0x24;
            direction = (((S_8016B230_1 *)arg3)->unk_45 +
                         ((s32)(((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 16) >> 25)) & 7;
            target_x = ((S_8016B230_7 *)target)->unk_24 +
                       ((u16 *)&D_8006CCD8)[direction];
            target_y = ((S_8016B230_7 *)target)->unk_25 +
                       ((u16 *)&D_8006CCE8)[direction];
            if ((((S_8016B230_2 *)arg2)->unk_24.at00.v == (u16)target_x) &&
                (((S_8016B230_2 *)arg2)->unk_24.at01.v == (u16)target_y)) {
                goto clear_history;
            }
            new_angle = func_800A0818(((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                                      target_x, (s16)target_y, arg0 + 0x98);
            ((S_8016B230_1 *)arg3)->unk_2A.u = new_angle;
            if ((func_8009A66C(new_angle, arg2, arg3, 0x20) << 16) <= 0) {
                u8 *retry_target = D_80082E80;

                ((S_8016B230_1 *)arg3)->unk_2A.u = func_800A0818(
                    ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                    ((S_8016B230_8 *)retry_target)->unk_24, ((S_8016B230_8 *)retry_target)->unk_25,
                    arg0 + 0x98);
            }
            {
                u8 *check_target = D_80082E80;

                if ((func_8009FD7C(((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                                   ((S_8016B230_9 *)check_target)->unk_24,
                                   ((S_8016B230_9 *)check_target)->unk_25) << 16) != 0) {
                    enabled = 1;
                }
            }
            i = 0;
            goto setup_loop;
        }
        goto use_target;
    }

    {
        s32 kind;

        kind = ((S_8016B230_2 *)arg2)->unk_26.s;
        if (kind >= 0) {
            u8 *kind_table = (u8 *)D_800E2970;

            if (((S_8016B230_10 *)(kind_table + kind * 0x14))->unk_0C & 2) {
                goto use_target;
            }
        }
    }
        i = 0;
        if (((S_8016B230_1 *)arg3)->unk_46 & 0x8000) {
            goto setup_loop;
        }
        found = func_800A04F0(arg3, ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                              ((S_8016B230_1 *)arg3)->unk_2A.s);
        if ((found != NULL) && (((S_8016B230_3 *)found)->unk_1C & 0x2000) &&
            (func_800A0134(found, arg3) < 0x81) &&
            ((func_8009A540(((s32)(((S_8016B230_1 *)arg3)->unk_2A.u << 16) >> 25) & 0xFFFF,
                            ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                            (s16)(((S_8016B230_1 *)arg3)->unk_88 - 0x20)) << 16) != 0)) {
            goto clear_history;
        }
        if (((S_8016B230_1 *)arg3)->unk_1C & 0x20000) {
            u8 *target = D_80082E80;
            ((S_8016B230_1 *)arg3)->unk_2A.u = func_800A0818(
                ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                ((S_8016B230_7 *)target)->unk_24, ((S_8016B230_7 *)target)->unk_25, arg0 + 0x98);
            if ((func_8009FD7C(((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                               ((S_8016B230_7 *)target)->unk_24, ((S_8016B230_7 *)target)->unk_25) << 16) != 0) {
                if (func_800A0134(D_800814A8, arg3) < 0x81) {
                    ret = func_8009A540(
                        ((s32)(((S_8016B230_1 *)arg3)->unk_2A.u << 16) >> 25) & 0xFFFF,
                        ((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                        (s16)(((S_8016B230_1 *)arg3)->unk_88 - 0x20));
                    i = 0;
                    if ((ret << 16) == 0) {
                        goto setup_loop;
                    }
                    goto clear_history;
                }
                i = 0;
                goto setup_loop;
            }
            goto init_loop;
        }

use_target:
    func_800A0E6C(arg2, ((S_8016B230_5 *)arg0)->unk_9C.s, arg3, arg0 + 0x98);
init_loop:
    i = 0;
setup_loop:
    x_table = (u8 *)&D_8006CCD8;
    delta = &D_8006CD00;
    ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(x_table);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

loop:
    base_wide = (s32)((S_8016B230_1 *)arg3)->unk_2A.s;
    if (((S_8016B230_5 *)arg0)->unk_98 & 2) {
        {
            s32 delta_wide = (s32)*delta;

            move_angle = (s16)(base_wide - delta_wide);
        }
    } else {
        {
            s32 delta_wide = (s32)*delta;

            move_angle = (s16)(base_wide + delta_wide);
        }
    }
    if ((func_8009A66C(move_angle, arg2, arg3, 0x20) << 16) > 0) {
        if (i >= 3) {
            s32 enabled_test = enabled;

            ASM_KEEP(enabled_test);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (enabled_test) {
                goto clear_history;
            }
        }
        ((S_8016B230_1 *)arg3)->unk_2A.u = move_angle;
        ((S_8016B230_13 *)(arg3 + (((S_8016B230_1 *)arg3)->unk_71.u & 0x7F)))->unk_74 =
            ((S_8016B230_2 *)arg2)->unk_24.at00.v;
        ((S_8016B230_13 *)(arg3 + (((S_8016B230_1 *)arg3)->unk_71.u & 0x7F)))->unk_7C =
            ((S_8016B230_2 *)arg2)->unk_24.at01.v;
        ((S_8016B230_1 *)arg3)->unk_71.u++;
        func_8009A3D0(((S_8016B230_2 *)arg2)->unk_24.at00.v, ((S_8016B230_2 *)arg2)->unk_24.at01.v,
                      (((S_8016B230_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        direction_index = (((S_8016B230_1 *)arg3)->unk_2A.u >> 8) & 0xE;
        ((S_8016B230_2 *)arg2)->unk_24.at00.v +=
            *((u8 *)((u32)direction_index + (u32)x_table));
        ((S_8016B230_2 *)arg2)->unk_24.at01.v += *((u8 *)&D_8006CCE8 + direction_index);
        call_x = ((S_8016B230_2 *)arg2)->unk_24.at00.v;
        call_y = *(volatile u8 *)((u8 *)arg2 + 0x25);
        step = 0x3000;
        if (((S_8016B230_1 *)arg3)->unk_1C & 0x2000) {
            step = 0x300;
        }
        func_8009A21C(call_x, call_y, step);
        goto after_loop;
    }

    if (i == 0) {
        if ((((S_8016B230_11 *)(&D_80082EA4))->unk_00 != ((S_8016B230_2 *)arg2)->unk_24.at00u.v) &&
            ((s16)func_8009A180(arg3, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) != 0)) {
            goto end;
        }
    }
    i++;
    delta++;
    if (i < 8) {
        goto loop;
    }

after_loop:
    loop_test = i < 8;
    if (!loop_test) {
        ((S_8016B230_1 *)arg3)->unk_71.u &= 0x7F;
        ((S_8016B230_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A9A0C(arg3);
        goto end;
    }
    loop_state = (u8 *)&D_80083460;
    ((S_8016B230_1 *)arg3)->unk_46 &= 0x7FFF;
    ((S_8016B230_5 *)arg0)->unk_9C.u = ((S_8016B230_2 *)arg2)->unk_26.u;
    ((S_8016B230_1 *)arg3)->unk_6D.u--;
    ((S_8016B230_12 *)loop_state)->unk_08++;
    if (((S_8016B230_1 *)arg3)->unk_6D.s != 0) {
        goto update_height;
    }

clear_history:
    ((S_8016B230_1 *)arg3)->unk_71.u &= 0x7F;
    goto end;

update_height:
    i = func_800BCB04((((S_8016B230_2 *)arg2)->unk_24.at00.v << 6) | 0x20,
                      (((S_8016B230_2 *)arg2)->unk_24.at01.v << 6) | 0x20,
                      (s16)(((S_8016B230_1 *)arg3)->unk_88 - 0x20));
    if (i < 0x200) {
        ((S_8016B230_1 *)arg3)->unk_88 = i;
    }
    goto end;

end:
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return;
}
