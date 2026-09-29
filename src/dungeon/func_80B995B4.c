#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172DB4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172DB4_0;   /* arg0 in func_80172DB4 */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s32 D_80170E9C;
extern s32 D_80174F18;


/* Updates decaying movement and tile alignment before advancing or finishing the action. */
void func_80172DB4(S_80172DB4_0 *action, EntityRec *motion, Rec_D_80082E80 *tile_state, EntityRec *actor_data)
{
    s16 timer;
    s32 tracked_actor;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(actor_data);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) +
                     ((actor_data->unk_6A >> 8) & 0xE)) << 19;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) +
                     ((actor_data->unk_6A >> 8) & 0xE)) << 19;
        action->unk_9B++;

        if (actor_data->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, tile_state, &D_80174F18);
            return;
        }
        if (tile_state->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (actor_data->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
                /* fall through */

    case 1:
    {
        s32 velocity_x = motion->unk_0C;
        motion->unk_0C = velocity_x - velocity_x / 4;
    }
        {
            s32 velocity_y = motion->unk_10;
            motion->unk_10 = velocity_y - velocity_y / 4;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile_state->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (actor_data->unk_28 != 0) {
            action->unk_96.s = 8;
            action->unk_9B++;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, tile_state, &D_80174F18);
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer > 0) {
            {
                s32 target_pos = tile_state->unk_24 << 6;
                s32 current_pos = motion->x.w.i - 0x20;
                motion->unk_0C =
                    ((target_pos - current_pos) << 16) / timer;
            }
            {
                s32 target_pos = tile_state->unk_25 << 6;
                s32 current_pos = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((target_pos - current_pos) << 16) / action->unk_96.s;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        if ((tile_state->unk_14.at00_u16.v & 0x6000) &&
            ((EntityRec *)actor_data)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, tile_state, &D_80174F18);
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, tile_state->unk_24, tile_state->unk_25);

            tracked_actor = ((s32)dungeonStatus.unk_10);
            if (tracked_actor == (s32)((u8 *)actor_data - 0x20)) {
                dungeonStatus.unk_10 = tracked_actor & 0x7FFFFFFF;
            }
            action->unk_8C = &D_80170E9C;
            return;
        }

    default:
        return;
    }
}
