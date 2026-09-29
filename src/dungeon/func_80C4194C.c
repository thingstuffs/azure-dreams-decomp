#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8017314C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017314C_1;   /* arg0 in func_8017314C */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170E7C;
extern u8 D_80174D5C;

/* Updates directional movement, decelerates it, and recenters the actor on its tile. */
void func_8017314C(S_8017314C_1 *action, EntityRec *motion, Rec_D_80082E80 *actor, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 19;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 19;
        action->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, actor, &D_80174D5C);
            return;
        }
        if (actor->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)source)->flags1C & 0x228) {
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
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 14;
        motion->unk_10 -=
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (actor->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, actor, &D_80174D5C);
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 tile_x;
                s32 current_x;

                tile_x = actor->unk_24 << 6;
                current_x = motion->x.w.i - 0x20;
                motion->unk_0C =
                    ((tile_x - current_x) << 15) >> 1;
            }
            {
                s32 tile_y;
                s32 current_y;

                tile_y = actor->unk_25 << 6;
                current_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((tile_y - current_y) << 15) >> 1;
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
        func_800A2B04(motion, actor->unk_24, actor->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E7C;
        return;

    default:
        return;
    }
}
