#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172CE0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172CE0_0;   /* arg0 in func_80172CE0 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s32 D_80171058;
extern s32 D_801748C0;

/* Applies backward motion, then returns the actor to its tile center or starts the next action. */
void func_80172CE0(S_80172CE0_0 *action, EntityRec *motion, Rec_D_80082E80 *entity, void *actor)
{
    s16 frames_left;
    s32 tracked_actor;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        motion->unk_0C =
            -((s16 *)((s8 *)dirStepX))[((u16)((s16)((EntityRec *)actor)->unk_6A) >> 9) & 7] << 15;
        motion->unk_10 =
            -((s16 *)((s8 *)dirStepY))[((u16)((s16)((EntityRec *)actor)->unk_6A) >> 9) & 7] << 15;
        action->unk_9B++;

        if (((EntityRec *)actor)->unk_28 == 0) {
            goto start_action;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)actor)->flags1C & 0x228) {
            frames_left = 8;
        } else {
            frames_left = -1;
        }
        action->unk_96.s = frames_left;
        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;

    case 1:
        motion->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[((u16)((s16)((EntityRec *)actor)->unk_6A) >> 9) & 7] << 10;
        motion->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[((u16)((s16)((EntityRec *)actor)->unk_6A) >> 9) & 7] << 10;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, entity, &D_801748C0);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        frames_left = action->unk_96.s;
        if (frames_left != 0) {
            {
                s32 target_x = entity->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->unk_0C =
                    ((target_x - current_x) << 15) / frames_left;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->unk_10 =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
            }
        }
        frames_left = action->unk_96.u - 1;
        action->unk_96.s = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        tracked_actor = ((s32)dungeonStatus.unk_10);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            dungeonStatus.unk_10 = tracked_actor & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80171058;
        return;

    default:
        return;
    }
}
