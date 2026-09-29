#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80155234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80155234_0;   /* arg0 in func_80155234 */





extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_80152E7C;
extern u8 D_80156C44[];
extern u8 D_80156C74[];

/* Update directional actor motion and settle at the destination tile center. */
void func_80155234(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s16 timer;
    s32 tracked_actor;

    switch (((S_80155234_0 *)action)->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        motion->unk_0C =
            -((s16 *)((s8 *)dirStepX))[(actor->unk_6A >> 9) & 7] << 15;
        motion->unk_10 =
            -((s16 *)((s8 *)dirStepY))[(actor->unk_6A >> 9) & 7] << 15;
        ((S_80155234_0 *)action)->unk_9B++;

        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, sprite, D_80156C74);
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80155234_0 *)action)->unk_96.s = 0;
            ((S_80155234_0 *)action)->unk_9B = 3;
            return;
        }

        if (((u32)actor->flags1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_80155234_0 *)action)->unk_96.s = timer;

        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;


    case 1:
        motion->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(actor->unk_6A >> 9) & 7] << 14;
        motion->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(actor->unk_6A >> 9) & 7] << 14;

        if (((S_80155234_0 *)action)->unk_96.s > 0) {
            ((S_80155234_0 *)action)->unk_96.s = ((S_80155234_0 *)action)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80155234_0 *)action)->unk_96.s = 0;
        }

        if (((S_80155234_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, sprite, D_80156C74);
        } else {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80156C44;
            func_80047784(
                sprite,
                D_80156C44[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80155234_0 *)action)->unk_9B++;
        }
        return;

    case 2:
        motion->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(actor->unk_6A >> 9) & 7] << 14;
        motion->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(actor->unk_6A >> 9) & 7] << 14;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80156C44;
        func_80047784(
            sprite,
            D_80156C44[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80155234_0 *)action)->unk_96.s = 8;
        ((S_80155234_0 *)action)->unk_9B++;
        return;

    case 3:
        timer = ((S_80155234_0 *)action)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((target_y - current_y) << 15) / ((S_80155234_0 *)action)->unk_96.s;
            }
        }

        timer = ((S_80155234_0 *)action)->unk_96.u - 1;
        ((S_80155234_0 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        motion->x.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
        motion->y.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        tracked_actor = ((s32)dungeonStatus.unk_10);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            dungeonStatus.unk_10 = tracked_actor & 0x7FFFFFFF;
        }
        ((S_80155234_0 *)action)->unk_8C = &D_80152E7C;

        return;

    default:
        return;
    }
}
