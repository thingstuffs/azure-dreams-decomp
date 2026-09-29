#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8017345C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017345C_1;   /* arg0 in func_8017345C */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170E94;
extern u8 D_80174ABC[];


/* Updates directional motion and returns the entity to its tile when the timer expires. */
void func_8017345C(S_8017345C_1 *action, EntityRec *motion, Rec_D_80082E80 *tile, EntityRec *entity)
{
    s16 timer;
    s32 tracked_entity;
    s32 direction;

    direction = (entity->unk_6A >> 9) & 7;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C = ((s16 *)((s8 *)dirStepX))[direction] << 17;
        motion->unk_10 = ((s16 *)((s8 *)dirStepY))[direction] << 17;
        action->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, tile, D_80174ABC);
            return;
        }
        if (tile->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (entity->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;
                /* fall through */

    case 1:
        motion->unk_0C -=
            ((s16 *)((s8 *)dirStepX))[direction] << 14;
        motion->unk_10 -=
            ((s16 *)((s8 *)dirStepY))[direction] << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, tile, D_80174ABC);
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = tile->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->unk_0C =
                    ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = tile->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, tile->unk_24,
                      tile->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E94;
        return;

    default:
        return;
    }
}
