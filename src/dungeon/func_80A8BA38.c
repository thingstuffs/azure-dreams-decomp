#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8015B238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8015B238_1;   /* arg0 in func_8015B238 */

typedef struct S_8015B238_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8015B238_2;   /* arg1 in func_8015B238 */




extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80158E54;
extern u8 D_8015C150[];
extern u8 D_8015C178[];

/* Updates directional movement and settles the actor at its tile center. */
void func_8015B238(void *motion_state, void *motion, void *map_actor, void *actor)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_actor;
    s32 *tracking_data;

    direction = (((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 9) & 7;
    state = ((S_8015B238_1 *)motion_state)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    func_800AD4D0(actor);
    ((S_8015B238_2 *)motion)->unk_0C = ((s16 *)&D_8006CCD8)[direction] << 18;
    ((S_8015B238_2 *)motion)->unk_10 = ((s16 *)&D_8006CCE8)[direction] << 18;
    ((S_8015B238_1 *)motion_state)->unk_9B++;

    if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
        goto stop_motion;
    }
    if (((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x8000) {
        ((S_8015B238_1 *)motion_state)->unk_96.s = 0;
        ((S_8015B238_1 *)motion_state)->unk_9B = 3;
        goto done;
    }

    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x228) {
        timer = 8;
    } else {
        timer = -1;
    }
    ((S_8015B238_1 *)motion_state)->unk_96.s = timer;

    ((S_8015B238_2 *)motion)->unk_0C -= ((S_8015B238_2 *)motion)->unk_0C / 4;
    ((S_8015B238_2 *)motion)->unk_10 -= ((S_8015B238_2 *)motion)->unk_10 / 4;

state_one:
    ((S_8015B238_2 *)motion)->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
    ((S_8015B238_2 *)motion)->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;

    if (((S_8015B238_1 *)motion_state)->unk_96.s > 0) {
        ((S_8015B238_1 *)motion_state)->unk_96.s = ((S_8015B238_1 *)motion_state)->unk_96.u - 1;
    } else if (((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x6000) {
        ((S_8015B238_1 *)motion_state)->unk_96.s = 0;
    }

    if (((S_8015B238_1 *)motion_state)->unk_96.s != 0) {
        goto done;
    }
    if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
        goto continue_state_one;
    }

stop_motion:
    ((S_8015B238_2 *)motion)->unk_14 = 0;
    ((S_8015B238_2 *)motion)->unk_10 = 0;
    ((S_8015B238_2 *)motion)->unk_0C = 0;
    func_800AAA54(motion_state, motion, map_actor, D_8015C178);
    goto done;

continue_state_one:
    (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_8015C150;
    func_80047784(
        map_actor,
        D_8015C150[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_8015B238_1 *)motion_state)->unk_9B++;
    goto done;

state_two:
    ((S_8015B238_2 *)motion)->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
    ((S_8015B238_2 *)motion)->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;
    if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x6000)) {
        goto done;
    }

    (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_8015C150;
    func_80047784(
        map_actor,
        D_8015C150[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_8015B238_1 *)motion_state)->unk_96.s = 8;
    ((S_8015B238_1 *)motion_state)->unk_9B++;
    goto done;

state_three:
    timer = ((S_8015B238_1 *)motion_state)->unk_96.s;
    if (timer != 0) {
        {
            s32 target_coord = ((Rec_D_80082E80 *)map_actor)->unk_24 << 6;
            s32 current_coord = ((S_8015B238_2 *)motion)->unk_00.at02.v - 0x20;
            ((S_8015B238_2 *)motion)->unk_0C = ((target_coord - current_coord) << 15) / timer;
        }
        {
            s32 target_coord = ((Rec_D_80082E80 *)map_actor)->unk_25 << 6;
            s32 current_coord = ((S_8015B238_2 *)motion)->unk_04.at02.v - 0x20;
            ((S_8015B238_2 *)motion)->unk_10 =
                ((target_coord - current_coord) << 15) / ((S_8015B238_1 *)motion_state)->unk_96.s;
        }
    }

    timer = ((S_8015B238_1 *)motion_state)->unk_96.u - 1;
    ((S_8015B238_1 *)motion_state)->unk_96.s = timer;
    if ((s32)(timer << 16) > 0) {
        goto done;
    }

    ((S_8015B238_2 *)motion)->unk_14 = 0;
    ((S_8015B238_2 *)motion)->unk_10 = 0;
    ((S_8015B238_2 *)motion)->unk_0C = 0;
    ((S_8015B238_2 *)motion)->unk_00.at00.v = ((((Rec_D_80082E80 *)map_actor)->unk_24 << 6) + 0x20) << 16;
    ((S_8015B238_2 *)motion)->unk_04.at00.v = ((((Rec_D_80082E80 *)map_actor)->unk_25 << 6) + 0x20) << 16;
    func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);

    tracking_data = &D_80083460;
    tracked_actor = tracking_data[4];
    if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
        tracking_data[4] = tracked_actor & 0x7FFFFFFF;
    }
    ((S_8015B238_1 *)motion_state)->unk_8C = &D_80158E54;

done:
    return;
}
