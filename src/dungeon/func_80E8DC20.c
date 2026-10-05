#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173420_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173420_0;   /* arg0 in func_80173420 */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_801710F4[];
extern u8 D_80174F10[];

/* Update directional motion, then settle the entity at its grid position. */
void func_80173420(S_80173420_0 *action, EntityRec *motion, Rec_D_80082E80 *grid_pos, EntityRec *entity)
{
    s16 *direction_y;
    s32 velocity_y;
    s32 decel_offset;
    s32 direction;
    s32 launch_offset;
    s32 velocity_x;
    s32 biased_velocity_x;
    s32 biased_velocity_y;
    s32 tracked_entity;
    s16 *directions_x;
    s32 ticks_left;
    s32 phase;
    u16 duration;
    s32 target_x;
    s32 current_x;
    s32 target_y;
    s32 current_y;

    ticks_left = action->unk_96.s - 1;
    direction = (entity->unk_6A >> 9) & 7;
    phase = action->unk_9B;
    action->unk_96.s = ticks_left;
    switch (phase) {
    case 0:
        func_800AD4D0(entity);
        directions_x = (s16 *)((s8 *)dirStepX);
        launch_offset = direction * 2;
        motion->unk_0C =
            *(s16 *)((u8 *)directions_x + launch_offset) << 0x12;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + launch_offset) << 0x12;
        action->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, grid_pos, D_80174F10);
            return;
        }
        if (grid_pos->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }

        duration = 6;
        if (entity->flags1C & 0x228) {
            duration = 8;
        }
        action->unk_96.s = duration;

        velocity_x = motion->unk_0C;
        biased_velocity_x = velocity_x;
        if (velocity_x < 0) {
            biased_velocity_x = velocity_x + 3;
        }
        velocity_y = motion->unk_10;
        motion->unk_0C = velocity_x - (biased_velocity_x >> 2);
        biased_velocity_y = velocity_y;
        motion->unk_10 = velocity_y - (biased_velocity_y / 4);
                        /* fall through */
    case 1:
        directions_x = (s16 *)((s8 *)dirStepX);
        decel_offset = direction * 2;
        direction_y = (s16 *)((u8 *)((s8 *)dirStepY) + decel_offset);
        motion->unk_0C -=
            *(s16 *)((u8 *)directions_x + decel_offset) << 0xE;
        motion->unk_10 -= *direction_y << 0xE;

        if (action->unk_96.u != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, grid_pos, D_80174F10);
        } else {
            action->unk_96.s = 6;
            action->unk_9B++;
        }
        return;
    case 2:
        if ((ticks_left << 0x10) != 0) {
            target_x = grid_pos->unk_24 << 6;
            current_x = motion->x.w.i - 0x20;
            motion->unk_0C = (target_x - current_x) << 0x10 >> 1;
            target_y = grid_pos->unk_25 << 6;
            current_y = motion->y.w.i - 0x20;
            motion->unk_10 = (target_y - current_y) << 0x10 >> 1;

            if (action->unk_96.u > 0) {
                return;
            }
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, grid_pos->unk_24, grid_pos->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = D_801710F4;
        break;
    default:
        return;
    }
}
