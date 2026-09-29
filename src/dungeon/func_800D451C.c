#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800D9C7C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D9C7C_1;   /* arg0 in func_800D9C7C */




extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_800D8C64[];
extern u8 D_8017586C[];
extern u8 D_8017588C[];


/* Updates directional movement, decelerates it, and settles the entity at its tile. */
void func_800D9C7C(S_800D9C7C_1 *controller, EntityRec *motion, Rec_D_80082E80 *entity, EntityRec *source)
{
    s16 ticks_left;
    s32 direction;
    s32 tracked_entity;

    direction = (source->unk_6A >> 9) & 7;
    switch (controller->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 18;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 18;
        controller->unk_9B++;

        if (source->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(controller, motion, entity, 0);
            return;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }
        if (source->flags1C & 0x228) {
            ticks_left = 8;
        } else {
            ticks_left = -1;
        }
        controller->unk_96.s = ticks_left;
        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;
        /* fall through */

    case 1:
        motion->unk_0C -=
            *(s16 *)((u8 *)((s8 *)dirStepX) + (direction * 2)) << 14;
        motion->unk_10 -=
            *(s16 *)((u8 *)((s8 *)dirStepY) + (direction * 2)) << 14;
        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
            controller->unk_96.s = 0;
        }
        if (controller->unk_96.s != 0) {
            return;
        }
        if (source->unk_28 != 0) {
            goto increment_state;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(controller, motion, entity, 0);
        return;

increment_state:
        controller->unk_96.s = 8;
        controller->unk_9B++;
        return;

    case 2:
        if (controller->unk_96.s != 0) {
            {
                s32 target_x = entity->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->unk_0C = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->unk_10 = ((target_y - current_y) << 15) >> 1;
            }
        }
        ticks_left = controller->unk_96.u - 1;
        controller->unk_96.s = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        controller->unk_8C = D_800D8C64;
        return;

    default:
        return;
    }
}
