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

/* Update motion and terrain collisions, then settle at a target or finish falling. */
void func_801747F0(void *motion, void *position, void *object)
{
    static void *const jump_targets[] = { &&distance_zero, &&distance_one, &&distance_two, &&distance_three, &&distance_four };
    u8 colors[4];
    s32 move_frames;
    s32 fall_height;
    s32 flight_height;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 cell_y;
    s16 frames_left;
    u16 next_scale;
    u16 height;
    u32 tile_distance;
    u8 *direction;
    u8 *directions;
    s32 target_cell_y;
    s32 next_cell_x;
    s32 next_cell_y;

settle:
    if (((S_801747F0_0 *)motion)->unk_1C.s != 1) {
        goto fall;
    }
    if (((S_801747F0_0 *)motion)->unk_1E.s != 0) {
        goto interpolate;
    }
    ((S_801747F0_0 *)motion)->unk_1E.u = (u16)(((S_801747F0_0 *)motion)->unk_1E.u + 1);
    cell_y = ((S_801747F0_0 *)motion)->unk_51.s;
    dx = ((S_801747F0_1 *)position)->unk_0E - ((S_801747F0_0 *)motion)->unk_50.s;
    target_cell_y = ((S_801747F0_1 *)position)->unk_12;
    if (dx < 0) {
        dx = -dx;
    }
    dy = target_cell_y - cell_y;
    if (dy < 0) {
        dy = -dy;
    }
    tile_distance = dx + dy;
    if (tile_distance >= 5U) {
        goto max_duration;
    }
    (void)jump_targets;
    goto *D_80170870[tile_distance];
distance_zero:
    move_frames = 4;
    goto set_duration;
distance_one:
    move_frames = 8;
    goto set_duration;
distance_two:
    move_frames = 0xC;
    goto set_duration;
distance_three:
    move_frames = 0xE;
    goto set_duration;
distance_four:
max_duration:
    move_frames = 0x10;
set_duration:
    ((S_801747F0_0 *)motion)->unk_26.u = move_frames;
interpolate:
    frames_left = ((S_801747F0_0 *)motion)->unk_26.u - 1;
    ((S_801747F0_0 *)motion)->unk_26.u = frames_left;
    if (frames_left != 0) {
        s32 next_x;
        s32 dest_cell_y;
        {
            s32 step_x;
            s32 offset_x;
            step_x = ((S_801747F0_1 *)position)->unk_0E << 6;
            offset_x = ((S_801747F0_1 *)position)->unk_00.at02.v - 0x20;
            step_x -= offset_x;
            step_x /= frames_left;
            next_x = (u16)((S_801747F0_1 *)position)->unk_00.at02.v + step_x;
            ASM_KEEP(step_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            dest_cell_y = ((S_801747F0_1 *)position)->unk_12;
            ((S_801747F0_1 *)position)->unk_00.at02.v = next_x;
        }
        {
            s32 step_y;
            s32 offset_y;
            step_y = dest_cell_y << 6;
            offset_y = ((S_801747F0_1 *)position)->unk_04.at02.v - 0x20;
            step_y -= offset_y;
            step_y /= ((S_801747F0_0 *)motion)->unk_26.s;
            ((S_801747F0_1 *)position)->unk_04.at02.v = (u16)((S_801747F0_1 *)position)->unk_04.at02.v + step_y;
        }
        ((S_801747F0_1 *)position)->unk_08.at02.v = (u16)((S_801747F0_1 *)position)->unk_08.at02.v +
            ((((S_801747F0_1 *)position)->unk_16 - ((S_801747F0_1 *)position)->unk_08.at02.v) /
             ((S_801747F0_0 *)motion)->unk_26.s);
    }
    if (((S_801747F0_0 *)motion)->unk_26.s <= 0) {
        colors[0] = ((S_801747F0_0 *)motion)->unk_2C;
        colors[1] = ((S_801747F0_0 *)motion)->unk_2D;
        colors[2] = ((S_801747F0_0 *)motion)->unk_2E;
        colors[3] = ((S_801747F0_0 *)motion)->unk_2F;
        func_800A7A7C(((S_801747F0_1 *)position)->unk_0E, ((S_801747F0_1 *)position)->unk_12,
                      ((S_801747F0_1 *)position)->unk_16, ((S_801747F0_2 *)object)->unk_08, colors);
        goto finished;
    }
    if (((S_801747F0_2 *)object)->unk_14 & 0x8000) {
        goto settle;
    }

fall:
    if (((S_801747F0_0 *)motion)->unk_1C.s != 2) {
        goto flight;
    }
    ((S_801747F0_1 *)position)->unk_08.at00.v += ((S_801747F0_0 *)motion)->unk_5C;
    ((S_801747F0_0 *)motion)->unk_5C += ((S_801747F0_0 *)motion)->unk_68;
    next_scale = ((S_801747F0_2 *)object)->unk_1E - 0xC8;
    ((S_801747F0_2 *)object)->unk_1E = next_scale;
    ((S_801747F0_2 *)object)->unk_1C = next_scale;
    {
        register s32 fall_cell_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 fall_cell_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        fall_cell_x = ((S_801747F0_0 *)motion)->unk_50.s;
        fall_cell_y = ((S_801747F0_0 *)motion)->unk_51.s;
        height = ((S_801747F0_1 *)position)->unk_08.at02u.v;
        fall_height = ((S_801747F0_1 *)position)->unk_08.at02.v;
        if ((func_800BCB04((fall_cell_x << 6) & 0xFFC0,
                           (fall_cell_y << 6) & 0xFFC0,
                           (s16)(height - 0x20)) - 7) < fall_height) {
            ((S_801747F0_1 *)position)->unk_08.at02.v = func_800BCB04(
                (((S_801747F0_0 *)motion)->unk_50.s << 6) & 0xFFC0,
                (((S_801747F0_0 *)motion)->unk_51.s << 6) & 0xFFC0,
                (s16)(((S_801747F0_1 *)position)->unk_08.at02p.v - 0x20));
            ((S_801747F0_1 *)position)->unk_08.at00u.v = 0;
finished:
            (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
            return;
        }
    }
    if (((S_801747F0_2 *)object)->unk_14 & 0x8000) {
        goto fall;
    }

flight:
    if (((S_801747F0_0 *)motion)->unk_1C.s != 0) {
        return;
    }
    ((S_801747F0_1 *)position)->unk_00.at00.v += ((S_801747F0_0 *)motion)->unk_54;
    ((S_801747F0_0 *)motion)->unk_54 += ((S_801747F0_0 *)motion)->unk_60;
    ((S_801747F0_1 *)position)->unk_04.at00.v += ((S_801747F0_0 *)motion)->unk_58;
    {
        s32 velocity_y;
        s32 accel_y;
        velocity_y = ((S_801747F0_0 *)motion)->unk_58;
        accel_y = ((S_801747F0_0 *)motion)->unk_64;
        velocity_y += accel_y;
        directions = D_801755E0;
        ((S_801747F0_0 *)motion)->unk_58 = velocity_y;
    }
    direction = (((S_801747F0_0 *)motion)->unk_24 * 4) + directions;
    next_cell_x = ((S_801747F0_0 *)motion)->unk_50.s + ((S_801747F0_3 *)direction)->unk_00;
    x = ((S_801747F0_1 *)position)->unk_00.at02.v;
    if (x < 0) {
        x += 0x3F;
    }
    if (next_cell_x == (x >> 6)) {
        next_cell_y = ((S_801747F0_0 *)motion)->unk_51.s + ((S_801747F0_3 *)direction)->unk_02;
        y = ((S_801747F0_1 *)position)->unk_04.at02.v;
        if (y < 0) {
            y += 0x3F;
        }
        if (next_cell_y == (y >> 6)) {
            if ((func_800A45D8(((S_801747F0_1 *)position)->unk_00.at02u.v, ((S_801747F0_1 *)position)->unk_04.at02u.v,
                               ((S_801747F0_1 *)position)->unk_08.at02.v) << 16) != 0) {
                goto blocked;
            }
            if (func_800BCB04(((S_801747F0_1 *)position)->unk_00.at02u.v, ((S_801747F0_1 *)position)->unk_04.at02u.v,
                              ((S_801747F0_1 *)position)->unk_08.at02.v) >= 0x200) {
blocked:
                ((S_801747F0_1 *)position)->unk_00.at00.v -= ((S_801747F0_0 *)motion)->unk_54;
                ((S_801747F0_0 *)motion)->unk_54 = 0;
                ((S_801747F0_0 *)motion)->unk_60 = 0;
                ((S_801747F0_1 *)position)->unk_04.at00.v -= ((S_801747F0_0 *)motion)->unk_58;
                ((S_801747F0_0 *)motion)->unk_58 = 0;
                ((S_801747F0_0 *)motion)->unk_64 = 0;
            } else {
                ((S_801747F0_0 *)motion)->unk_50.u += *(u8 *)((((S_801747F0_0 *)motion)->unk_24 * 4) + directions);
                ((S_801747F0_0 *)motion)->unk_51.u += *(u8 *)((((S_801747F0_0 *)motion)->unk_24 * 4) + directions + 2);
            }
            ((S_801747F0_2 *)object)->unk_06 = 0;
        }
    }
    ((S_801747F0_1 *)position)->unk_08.at00.v += ((S_801747F0_0 *)motion)->unk_5C;
    ((S_801747F0_0 *)motion)->unk_5C += ((S_801747F0_0 *)motion)->unk_68;
    height = ((S_801747F0_1 *)position)->unk_08.at02u.v;
    flight_height = ((S_801747F0_1 *)position)->unk_08.at02.v;
    if ((func_800BCB04((((S_801747F0_0 *)motion)->unk_50.s << 6) & 0xFFC0,
                       (((S_801747F0_0 *)motion)->unk_51.s << 6) & 0xFFC0,
                       (s16)(height - 0x20)) - 0x10) < flight_height) {
        ((S_801747F0_1 *)position)->unk_08.at02.v = func_800BCB04(
            (((S_801747F0_0 *)motion)->unk_50.s << 6) & 0xFFC0,
            (((S_801747F0_0 *)motion)->unk_51.s << 6) & 0xFFC0,
            (s16)(((S_801747F0_1 *)position)->unk_08.at02p.v - 0x20));
        ((S_801747F0_1 *)position)->unk_08.at00u.v = 0;
        ((S_801747F0_0 *)motion)->unk_64 = 0;
        ((S_801747F0_0 *)motion)->unk_58 = 0;
        ((S_801747F0_0 *)motion)->unk_60 = 0;
        ((S_801747F0_0 *)motion)->unk_54 = 0;
        ((S_801747F0_0 *)motion)->unk_1C.u = ((S_801747F0_0 *)motion)->unk_1C.u + 1;
        if ((func_800A7234(((S_801747F0_0 *)motion)->unk_50.s, ((S_801747F0_0 *)motion)->unk_51.s,
                           (s16)(((S_801747F0_1 *)position)->unk_08.at02p.v - 0x20),
                           (s16 *)((u8 *)position + 0xE),
                           (s16 *)((u8 *)position + 0x12),
                           (s16 *)((u8 *)position + 0x16)) << 16) == 0) {
            ((S_801747F0_0 *)motion)->unk_1C.s = 2;
            ((S_801747F0_0 *)motion)->unk_5C = 0xFFF80000;
        }
    }
    if (((S_801747F0_2 *)object)->unk_14 & 0x8000) {
        goto flight;
    }
}
