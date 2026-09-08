#include "common.h"

typedef struct S_801747F0_0 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    u8 pad_20[0x4];
    s16 unk_24;
    union { u16 u; s16 s; } unk_26;   /* accessed as both */
    u8 pad_28[0x4];
    u8 unk_2C;
    u8 unk_2D;
    u8 unk_2E;
    u8 unk_2F;
    u8 pad_30[0x20];
    union { s8 s; u8 u; } unk_50;   /* accessed as both */
    union { s8 s; u8 u; } unk_51;   /* accessed as both */
    u8 pad_52[0x2];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_801747F0_0;   /* arg0 in func_801747F0 */

typedef struct S_801747F0_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; struct { u8 pad[0x2]; u16 v; } at02p; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_801747F0_1;   /* arg1 in func_801747F0 */

typedef struct S_801747F0_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801747F0_2;   /* arg2 in func_801747F0 */

typedef struct S_801747F0_3 {
    s16 unk_00;
    s16 unk_02;
} S_801747F0_3;   /* tile in func_801747F0 */



extern void *D_80170870[];
extern u8 D_801755E0[16];
extern s32 D_800814A0;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, u8 *);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_801748B8(void) __attribute__((noreturn));
extern void func_80174AA0(void) __attribute__((noreturn));
extern void func_80174C5C(void) __attribute__((noreturn));

void func_801747F0(void *arg0, void *arg1, void *arg2)
{
    static void *const jump_targets[] = { &&jt0, &&jt1, &&jt2, &&jt3, &&jt4 };
    u8 colors[4];
    s32 old_height;
    s32 old_height2;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 y_cell;
    u16 count;
    s16 count_after;
    u16 next_z;
    u16 z;
    u32 distance;
    u8 *tile;
    u8 *tile_base;
    s32 step;
    s32 target_y;
    s32 tile_x;
    s32 tile_y;

state1:
    if (((S_801747F0_0 *)arg0)->unk_1C.s != 1) {
        goto state2;
    }
    if (((S_801747F0_0 *)arg0)->unk_1E.s != 0) {
        goto move1;
    }
    ((S_801747F0_0 *)arg0)->unk_1E.u = (u16)(((S_801747F0_0 *)arg0)->unk_1E.u + 1);
    y_cell = ((S_801747F0_0 *)arg0)->unk_51.s;
    dx = ((S_801747F0_1 *)arg1)->unk_0E - ((S_801747F0_0 *)arg0)->unk_50.s;
    target_y = ((S_801747F0_1 *)arg1)->unk_12;
    if (dx < 0) {
        dx = -dx;
    }
    dy = target_y - y_cell;
    if (dy < 0) {
        dy = -dy;
    }
    distance = dx + dy;
    if (distance >= 5U) {
        goto far1;
    }
    (void)jump_targets;
    goto *D_80170870[distance];
jt0:
    {
        s32 result = 4;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801748B8();
        return;
    }
jt1:
    {
        s32 result = 8;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801748B8();
        return;
    }
jt2:
    {
        s32 result = 0xC;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801748B8();
        return;
    }
jt3:
    {
        s32 result = 0xE;
        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_801748B8();
        return;
    }
jt4:
far1:
    ((S_801747F0_0 *)arg0)->unk_26.u = 0x10;
move1:
    count_after = ((S_801747F0_0 *)arg0)->unk_26.u - 1;
    ((S_801747F0_0 *)arg0)->unk_26.u = count_after;
    if (count_after != 0) {
        s32 next_x;
        s32 next_target_y;
        {
            s32 interp_target;
            s32 interp_current;
            interp_target = ((S_801747F0_1 *)arg1)->unk_0E << 6;
            interp_current = ((S_801747F0_1 *)arg1)->unk_00.at02.v - 0x20;
            interp_target -= interp_current;
            interp_target /= count_after;
            next_x = (u16)((S_801747F0_1 *)arg1)->unk_00.at02.v + interp_target;
            ASM_KEEP(interp_target);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            next_target_y = ((S_801747F0_1 *)arg1)->unk_12;
            ((S_801747F0_1 *)arg1)->unk_00.at02.v = next_x;
        }
        {
            s32 interp_target_y;
            s32 interp_current_y;
            interp_target_y = next_target_y << 6;
            interp_current_y = ((S_801747F0_1 *)arg1)->unk_04.at02.v - 0x20;
            interp_target_y -= interp_current_y;
            interp_target_y /= ((S_801747F0_0 *)arg0)->unk_26.s;
            ((S_801747F0_1 *)arg1)->unk_04.at02.v = (u16)((S_801747F0_1 *)arg1)->unk_04.at02.v + interp_target_y;
        }
        ((S_801747F0_1 *)arg1)->unk_08.at02.v = (u16)((S_801747F0_1 *)arg1)->unk_08.at02.v +
            ((((S_801747F0_1 *)arg1)->unk_16 - ((S_801747F0_1 *)arg1)->unk_08.at02.v) /
             ((S_801747F0_0 *)arg0)->unk_26.s);
    }
    if (((S_801747F0_0 *)arg0)->unk_26.s <= 0) {
        colors[0] = ((S_801747F0_0 *)arg0)->unk_2C;
        colors[1] = ((S_801747F0_0 *)arg0)->unk_2D;
        colors[2] = ((S_801747F0_0 *)arg0)->unk_2E;
        colors[3] = ((S_801747F0_0 *)arg0)->unk_2F;
        func_800A7A7C(((S_801747F0_1 *)arg1)->unk_0E, ((S_801747F0_1 *)arg1)->unk_12,
                      ((S_801747F0_1 *)arg1)->unk_16, ((S_801747F0_2 *)arg2)->unk_08, colors);
        func_80174AA0();
        return;
    }
    if (((S_801747F0_2 *)arg2)->unk_14 & 0x8000) {
        goto state1;
    }

state2:
    if (((S_801747F0_0 *)arg0)->unk_1C.s != 2) {
        goto state0;
    }
    ((S_801747F0_1 *)arg1)->unk_08.at00.v += ((S_801747F0_0 *)arg0)->unk_5C;
    ((S_801747F0_0 *)arg0)->unk_5C += ((S_801747F0_0 *)arg0)->unk_68;
    next_z = ((S_801747F0_2 *)arg2)->unk_1E - 0xC8;
    ((S_801747F0_2 *)arg2)->unk_1E = next_z;
    ((S_801747F0_2 *)arg2)->unk_1C = next_z;
    {
        register s32 state2_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 state2_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        state2_x = ((S_801747F0_0 *)arg0)->unk_50.s;
        state2_y = ((S_801747F0_0 *)arg0)->unk_51.s;
        z = ((S_801747F0_1 *)arg1)->unk_08.at02u.v;
        old_height = ((S_801747F0_1 *)arg1)->unk_08.at02.v;
        if ((func_800BCB04((state2_x << 6) & 0xFFC0,
                           (state2_y << 6) & 0xFFC0,
                           (s16)(z - 0x20)) - 7) < old_height) {
            ((S_801747F0_1 *)arg1)->unk_08.at02.v = func_800BCB04(
                (((S_801747F0_0 *)arg0)->unk_50.s << 6) & 0xFFC0,
                (((S_801747F0_0 *)arg0)->unk_51.s << 6) & 0xFFC0,
                (s16)(((S_801747F0_1 *)arg1)->unk_08.at02p.v - 0x20));
            ((S_801747F0_1 *)arg1)->unk_08.at00u.v = 0;
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
            return;
        }
    }
    if (((S_801747F0_2 *)arg2)->unk_14 & 0x8000) {
        goto state2;
    }

state0:
    if (((S_801747F0_0 *)arg0)->unk_1C.s != 0) {
        return;
    }
    ((S_801747F0_1 *)arg1)->unk_00.at00.v += ((S_801747F0_0 *)arg0)->unk_54;
    ((S_801747F0_0 *)arg0)->unk_54 += ((S_801747F0_0 *)arg0)->unk_60;
    ((S_801747F0_1 *)arg1)->unk_04.at00.v += ((S_801747F0_0 *)arg0)->unk_58;
    {
        register s32 current_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 accel_y;
        current_y = ((S_801747F0_0 *)arg0)->unk_58;
        accel_y = ((S_801747F0_0 *)arg0)->unk_64;
        current_y += accel_y;
        tile_base = D_801755E0;
        ASM_USE(tile_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        ((S_801747F0_0 *)arg0)->unk_58 = current_y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }
    tile = (((S_801747F0_0 *)arg0)->unk_24 * 4) + tile_base;
    tile_x = ((S_801747F0_0 *)arg0)->unk_50.s + ((S_801747F0_3 *)tile)->unk_00;
    x = ((S_801747F0_1 *)arg1)->unk_00.at02.v;
    if (x < 0) {
        x += 0x3F;
    }
    if (tile_x == (x >> 6)) {
        tile_y = ((S_801747F0_0 *)arg0)->unk_51.s + ((S_801747F0_3 *)tile)->unk_02;
        y = ((S_801747F0_1 *)arg1)->unk_04.at02.v;
        if (y < 0) {
            y += 0x3F;
        }
        if (tile_y == (y >> 6)) {
            if ((func_800A45D8(((S_801747F0_1 *)arg1)->unk_00.at02u.v, ((S_801747F0_1 *)arg1)->unk_04.at02u.v,
                               ((S_801747F0_1 *)arg1)->unk_08.at02.v) << 16) != 0) {
                goto blocked;
            }
            if (func_800BCB04(((S_801747F0_1 *)arg1)->unk_00.at02u.v, ((S_801747F0_1 *)arg1)->unk_04.at02u.v,
                              ((S_801747F0_1 *)arg1)->unk_08.at02.v) >= 0x200) {
blocked:
                ((S_801747F0_1 *)arg1)->unk_00.at00.v -= ((S_801747F0_0 *)arg0)->unk_54;
                ((S_801747F0_0 *)arg0)->unk_54 = 0;
                ((S_801747F0_0 *)arg0)->unk_60 = 0;
                ((S_801747F0_1 *)arg1)->unk_04.at00.v -= ((S_801747F0_0 *)arg0)->unk_58;
                ((S_801747F0_0 *)arg0)->unk_58 = 0;
                ((S_801747F0_0 *)arg0)->unk_64 = 0;
                func_80174C5C();
                return;
            }
            ((S_801747F0_0 *)arg0)->unk_50.u += *(u8 *)((((S_801747F0_0 *)arg0)->unk_24 * 4) + tile_base);
            ((S_801747F0_0 *)arg0)->unk_51.u += *(u8 *)((((S_801747F0_0 *)arg0)->unk_24 * 4) + tile_base + 2);
            ((S_801747F0_2 *)arg2)->unk_06 = 0;
        }
    }
    ((S_801747F0_1 *)arg1)->unk_08.at00.v += ((S_801747F0_0 *)arg0)->unk_5C;
    ((S_801747F0_0 *)arg0)->unk_5C += ((S_801747F0_0 *)arg0)->unk_68;
    z = ((S_801747F0_1 *)arg1)->unk_08.at02u.v;
    old_height2 = ((S_801747F0_1 *)arg1)->unk_08.at02.v;
    if ((func_800BCB04((((S_801747F0_0 *)arg0)->unk_50.s << 6) & 0xFFC0,
                       (((S_801747F0_0 *)arg0)->unk_51.s << 6) & 0xFFC0,
                       (s16)(z - 0x20)) - 0x10) < old_height2) {
        ((S_801747F0_1 *)arg1)->unk_08.at02.v = func_800BCB04(
            (((S_801747F0_0 *)arg0)->unk_50.s << 6) & 0xFFC0,
            (((S_801747F0_0 *)arg0)->unk_51.s << 6) & 0xFFC0,
            (s16)(((S_801747F0_1 *)arg1)->unk_08.at02p.v - 0x20));
        ((S_801747F0_1 *)arg1)->unk_08.at00u.v = 0;
        ((S_801747F0_0 *)arg0)->unk_64 = 0;
        ((S_801747F0_0 *)arg0)->unk_58 = 0;
        ((S_801747F0_0 *)arg0)->unk_60 = 0;
        ((S_801747F0_0 *)arg0)->unk_54 = 0;
        ((S_801747F0_0 *)arg0)->unk_1C.u = ((S_801747F0_0 *)arg0)->unk_1C.u + 1;
        if ((func_800A7234(((S_801747F0_0 *)arg0)->unk_50.s, ((S_801747F0_0 *)arg0)->unk_51.s,
                           (s16)(((S_801747F0_1 *)arg1)->unk_08.at02p.v - 0x20),
                           (s16 *)((u8 *)arg1 + 0xE),
                           (s16 *)((u8 *)arg1 + 0x12),
                           (s16 *)((u8 *)arg1 + 0x16)) << 16) == 0) {
            ((S_801747F0_0 *)arg0)->unk_1C.s = 2;
            ((S_801747F0_0 *)arg0)->unk_5C = 0xFFF80000;
        }
    }
    if (((S_801747F0_2 *)arg2)->unk_14 & 0x8000) {
        goto state0;
    }
}
