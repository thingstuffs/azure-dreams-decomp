#include "common.h"

typedef struct S_800B9998_0 {
    u8 pad_00[0x66];
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    u8 pad_68[0x30];
    s8 * unk_98;
} S_800B9998_0;   /* arg0 in func_800B9998 */

typedef struct S_800B9998_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x6];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800B9998_1;   /* town in func_800B9998 */

typedef struct S_800B9998_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B9998_2;   /* p1 in func_800B9998 */

typedef struct S_800B9998_3 {
    u8 pad_00[0x1A];
    union { u16 s; volatile u16 u; } unk_1A;   /* accessed as both */
} S_800B9998_3;   /* p2 in func_800B9998 */



extern s32 D_800814A0;
extern s32 D_80083780;

extern void func_80033D08(void *);
extern s32 func_8009CFE0(void *, void *);

/* Deactivate the object when triggered; otherwise update its spin from nearby motion and advance rotation. */
void func_800B9998(void *object, void *position, void *rotation) {
    register u8 *position_data ASM_REG("$17") = position;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *rotation_data = rotation;
    s8 *active_flag;
    u8 *town_state;
    s32 dx;
    s32 dy;
    s32 near_x;
    s32 speed_sq;
    s32 position_y;
    s32 spin_speed;
    s32 raw_speed;
    s32 angle_step;

    if (func_8009CFE0(object, position) != 0) {
        active_flag = ((S_800B9998_0 *)object)->unk_98;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        func_80033D08(object);
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto epilogue;
    }

    raw_speed = ((S_800B9998_0 *)object)->unk_66.s;
    spin_speed = ((S_800B9998_0 *)object)->unk_66.u;
    if (spin_speed >= 0x100) {
        ((S_800B9998_0 *)object)->unk_66.s = raw_speed - 0x20;
        goto speed_ready;
    }
    if (spin_speed >= 0x10) {
        ((S_800B9998_0 *)object)->unk_66.s = raw_speed - 0x10;
        goto speed_ready;
    }
    ((S_800B9998_0 *)object)->unk_66.s = 0;

    speed_ready:
    town_state = (u8 *)&D_80083780;
    dx = ((S_800B9998_1 *)town_state)->unk_02;
    dy = ((S_800B9998_2 *)position_data)->unk_02;
    position_y = ((S_800B9998_2 *)position_data)->unk_06;
    dx -= dy;
    if (dx < 0) {
        dx = -dx;
    }
    dx = (s16)dx;
    dy = ((S_800B9998_1 *)town_state)->unk_06;
    near_x = dx < 0x81;
    ASM_USE(near_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    dy -= position_y;
    if (dy < 0) {
        dy = -dy;
    }

    if (near_x && ((s16)dy < 0x81)) {
        speed_sq = (((S_800B9998_1 *)town_state)->unk_0E * ((S_800B9998_1 *)town_state)->unk_0E) +
              (((S_800B9998_1 *)town_state)->unk_12 * ((S_800B9998_1 *)town_state)->unk_12);
        ((S_800B9998_0 *)object)->unk_66.s =
            ((S_800B9998_0 *)object)->unk_66.s +
            ((s32)(speed_sq + ((u32)speed_sq >> 31)) >> 1);
    }

    if (((S_800B9998_0 *)object)->unk_66.u >= 0x601) {
        ((S_800B9998_0 *)object)->unk_66.s = 0x600;
    }

    angle_step = ((S_800B9998_0 *)object)->unk_66.s + 0x80;
    ((S_800B9998_3 *)rotation_data)->unk_1A.s = ((S_800B9998_3 *)rotation_data)->unk_1A.s + angle_step;
    ((S_800B9998_3 *)rotation_data)->unk_1A.u =
        ((S_800B9998_3 *)rotation_data)->unk_1A.u & 0xFFF;

epilogue:
    return;
}
