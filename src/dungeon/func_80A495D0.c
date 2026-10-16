#include "modules/dungeon_resource06_slot0.h"

void dungeonUpdateDirectionalMotionAndTile(R06_80172DD0_S_80172DD0_1 *action, EntityRec *motion, Rec_D_80082E80 *tile_state, EntityRec *entity)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;

    direction = (entity->unk_6A >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        dungeonApplyClampedActorValueDelta(entity);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 18;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 18;
        action->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            dungeonBeginActorDisplayAction(action, motion, tile_state, ((u8 *)D_8017586C));
            return;
        }
        if (tile_state->unk_14.at00_u16.v & 0x8000) {
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
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 14;
        motion->unk_10 -=
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile_state->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            action->unk_9B = 0;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            dungeonBeginActorDisplayAction(action, motion, tile_state, ((u8 *)D_8017588C));
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_coord = tile_state->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;

                motion->unk_0C = ((target_coord - current_coord) << 15) >> 1;
            }
            {
                s32 target_coord = tile_state->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;

                motion->unk_10 = ((target_coord - current_coord) << 15) >> 1;
            }
            motion->unk_0C += motion->unk_0C >> 1;
            motion->unk_10 += motion->unk_10 >> 1;
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, tile_state->unk_24, tile_state->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = ((u8 *)func_8017140C);
        return;

    default:
        return;
    }
}
