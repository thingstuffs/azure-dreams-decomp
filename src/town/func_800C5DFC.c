#include "common.h"


extern s32 func_800C30E0(void *arg0, void *arg1, void *arg2);
extern s16 func_800C2B38(void *arg0, s32 arg1, s32 arg2);
extern void func_800C37C4(void *arg0, void *arg1, void *arg2);
extern int abs(int);

extern s32 D_800D4FE8[4];
extern s32 D_800D4FF8[4];
extern s32 D_800D5008[4];
extern s32 D_800D5018[4];


typedef struct S_800C355C_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800C355C_0;   /* arg1 in func_800C355C */

typedef struct S_800C355C_1 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x10];
    union { s16 s; u16 u; } unk_84;   /* accessed as both */
    union { s16 s; u16 u; } unk_86;   /* accessed as both */
    u8 pad_88[0x4];
    union { s16 s; u16 u; } unk_8C;   /* accessed as both */
    union { s16 s; u16 u; } unk_8E;   /* accessed as both */
} S_800C355C_1;   /* arg0 in func_800C355C */

/* Advance motion, clamp at the facing boundary, and update directional speed. */
void func_800C355C(S_800C355C_1 *entity, void *motion, void *context)
{
    s32 pos_x;
    s32 step_y;
    s32 angle;
    s32 quadrant;
    s32 speed;
    s32 max_speed;
    s32 *motion_words;

    if (func_800C30E0(entity, motion, context) != 0) {
        return;
    }

    motion_words = (s32 *)motion;
    pos_x = motion_words[0];
    max_speed = motion_words[3];
    pos_x += max_speed;
    speed = *(volatile s32 *)((u8 *)motion + 4);
    step_y = motion_words[4];
    speed += step_y;
    ((S_800C355C_0 *)motion)->unk_00.at00.v = pos_x;
    ((S_800C355C_0 *)motion)->unk_04.at00.v = speed;
    ((S_800C355C_0 *)motion)->unk_0A = func_800C2B38(motion, max_speed, step_y);

    angle = 0x400 - entity->unk_72;
    quadrant = (angle / 0x400) & 3;

    if (quadrant == 1) {
        goto check_max_y;
    }
    if (quadrant < 2) {
        if (quadrant == 0) {
            goto check_max_x;
        }
        goto check_min_y;
    }
    if (quadrant == 2) {
        goto check_min_x;
    }
    goto check_min_y;

check_max_x:
    if (entity->unk_84.s + entity->unk_8C.s < ((S_800C355C_0 *)motion)->unk_00.at02.v) {
        ((S_800C355C_0 *)motion)->unk_00.at02u.v = entity->unk_84.u + entity->unk_8C.u;
        goto handle_boundary;
    }
    goto update_speed;

check_max_y:
    if (entity->unk_86.s + entity->unk_8E.s < ((S_800C355C_0 *)motion)->unk_04.at02.v) {
        ((S_800C355C_0 *)motion)->unk_04.at02u.v = entity->unk_86.u + entity->unk_8E.u;
        goto handle_boundary;
    }
    goto update_speed;

check_min_x:
    if (((S_800C355C_0 *)motion)->unk_00.at02.v < entity->unk_84.s - entity->unk_8C.s) {
        u16 center;
        u16 extent;
        center = entity->unk_84.u;
        extent = entity->unk_8C.u;
        ((S_800C355C_0 *)motion)->unk_00.at02u.v = center - extent;
        goto handle_boundary;
    }
    goto update_speed;

check_min_y:
    if (((S_800C355C_0 *)motion)->unk_04.at02.v < entity->unk_86.s - entity->unk_8E.s) {
        u16 center;
        u16 extent;
        center = entity->unk_86.u;
        extent = entity->unk_8E.u;
        ((S_800C355C_0 *)motion)->unk_04.at02u.v = center - extent;
    } else {
        goto update_speed;
    }

handle_boundary:
    func_800C37C4(entity, motion, context);
    return;

update_speed:
    max_speed = 0x20000;

    speed = ((S_800C355C_0 *)motion)->unk_0C + D_800D4FE8[quadrant];
    ((S_800C355C_0 *)motion)->unk_0C = speed;
    speed = abs(speed);
    speed = max_speed < speed;
    if (speed != 0) {
        ((S_800C355C_0 *)motion)->unk_0C = D_800D4FF8[quadrant];
    }

    speed = ((S_800C355C_0 *)motion)->unk_10 + D_800D5008[quadrant];
    ((S_800C355C_0 *)motion)->unk_10 = speed;
    speed = abs(speed);
    speed = max_speed < speed;
    if (speed != 0) {
        ((S_800C355C_0 *)motion)->unk_10 = D_800D5018[quadrant];
    }
}
