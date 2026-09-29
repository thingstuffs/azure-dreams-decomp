#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172FE4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FE4_0;   /* arg0 in func_80172FE4 */





extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170EA8;
extern s32 D_80174068;


/* Updates directional movement, then stops or returns the entity to its grid position. */
void func_80172FE4(S_80172FE4_0 *action, EntityRec *motion, Rec_D_80082E80 *entity, EntityRec *source)
{
    s16 timer;
    s32 current_x;
    s32 current_y;
    s32 target_x;
    s32 tracked_addr;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C =
            -*(s16 *)((u8 *)((s8 *)dirStepX) +
                      ((source->unk_6A >> 8) & 0xE)) << 15;
        motion->unk_10 =
            -*(s16 *)((u8 *)((s8 *)dirStepY) +
                      ((source->unk_6A >> 8) & 0xE)) << 15;
        action->unk_9B++;

        if (source->unk_28 == 0) {
            goto start_action;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (source->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;
        /* fall through */

    case 1:
        motion->unk_0C +=
            *(s16 *)((u8 *)((s8 *)dirStepX) +
                     ((source->unk_6A >> 8) & 0xE)) << 14;
        {
            s16 table_offset;
            u8 *y_table;

            table_offset = (source->unk_6A >> 8) & 0xE;
            y_table = (u8 *)((s8 *)dirStepY);
            motion->unk_10 +=
                *(s16 *)(y_table + table_offset) << 14;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (source->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, entity, &D_80174068);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            target_x = entity->unk_24 << 6;
            current_x = motion->x.w.i - 0x20;
            current_y = motion->y.w.i - 0x20;
            motion->unk_0C =
                ((target_x - current_x) << 15) /
                action->unk_96.s;
            motion->unk_10 =
                (((entity->unk_25 << 6) - current_y) << 15) /
                action->unk_96.s;
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        tracked_addr = ((s32)dungeonStatus.unk_10);
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            dungeonStatus.unk_10 = tracked_addr & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170EA8;
        return;

    default:
        return;
    }
}
