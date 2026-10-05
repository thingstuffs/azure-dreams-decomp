#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80167234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80167234_0;   /* arg0 in func_80167234 */

typedef struct S_80167234_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80167234_1;   /* arg1 in func_80167234 */


extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern void func_800AD4D0(void *);

extern u8 D_80164E7C;
extern u8 D_80168C44[];
extern u8 D_80168C74[];

/* Advance directional motion and settle the actor at its tile center. */
void func_80167234(void *motion_state, void *motion, void *sprite, void *actor)
{
    s32 state;
    s16 timer;
    s32 tracked_actor;

    state = ((S_80167234_0 *)motion_state)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(actor);
        ((S_80167234_1 *)motion)->unk_0C =
            -((s16 *)((s8 *)dirStepX))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 15;
        ((S_80167234_1 *)motion)->unk_10 =
            -((s16 *)((s8 *)dirStepY))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 15;
        ((S_80167234_0 *)motion_state)->unk_9B++;

        if (((EntityRec *)actor)->unk_28 == 0) {
            ((S_80167234_1 *)motion)->unk_14 = 0;
            ((S_80167234_1 *)motion)->unk_10 = 0;
            ((S_80167234_1 *)motion)->unk_0C = 0;
            func_800AAA54(motion_state, motion, sprite, D_80168C74);
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80167234_0 *)motion_state)->unk_96.s = 0;
            ((S_80167234_0 *)motion_state)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)actor)->flags1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_80167234_0 *)motion_state)->unk_96.s = timer;

        ((S_80167234_1 *)motion)->unk_0C -= ((S_80167234_1 *)motion)->unk_0C / 4;
        ((S_80167234_1 *)motion)->unk_10 -= ((S_80167234_1 *)motion)->unk_10 / 4;
                        /* fall through */

    case 1:
        ((S_80167234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        ((S_80167234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;

        if (((S_80167234_0 *)motion_state)->unk_96.s > 0) {
            ((S_80167234_0 *)motion_state)->unk_96.s = ((S_80167234_0 *)motion_state)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80167234_0 *)motion_state)->unk_96.s = 0;
        }

        if (((S_80167234_0 *)motion_state)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((S_80167234_1 *)motion)->unk_14 = 0;
            ((S_80167234_1 *)motion)->unk_10 = 0;
            ((S_80167234_1 *)motion)->unk_0C = 0;
            func_800AAA54(motion_state, motion, sprite, D_80168C74);
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80168C44;
        func_80047784(
            sprite,
            D_80168C44[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80167234_0 *)motion_state)->unk_9B++;
        return;

    case 2:
        ((S_80167234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        ((S_80167234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80168C44;
        func_80047784(
            sprite,
            D_80168C44[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80167234_0 *)motion_state)->unk_96.s = 8;
        ((S_80167234_0 *)motion_state)->unk_9B++;
        return;

    case 3:
        timer = ((S_80167234_0 *)motion_state)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = ((S_80167234_1 *)motion)->unk_00.at02.v - 0x20;
                ((S_80167234_1 *)motion)->unk_0C = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = ((S_80167234_1 *)motion)->unk_04.at02.v - 0x20;
                ((S_80167234_1 *)motion)->unk_10 =
                    ((target_y - current_y) << 15) / ((S_80167234_0 *)motion_state)->unk_96.s;
            }
        }

        timer = ((S_80167234_0 *)motion_state)->unk_96.u - 1;
        ((S_80167234_0 *)motion_state)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((S_80167234_1 *)motion)->unk_14 = 0;
        ((S_80167234_1 *)motion)->unk_10 = 0;
        ((S_80167234_1 *)motion)->unk_0C = 0;
        ((S_80167234_1 *)motion)->unk_00.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
        ((S_80167234_1 *)motion)->unk_04.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        tracked_actor = ((s32)dungeonStatus.unk_10);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            dungeonStatus.unk_10 = tracked_actor & 0x7FFFFFFF;
        }
        ((S_80167234_0 *)motion_state)->unk_8C = &D_80164E7C;
    }
}
