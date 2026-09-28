#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
extern int abs(int);


typedef struct S_80172F14_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F14_1;   /* arg0 in func_80172F14 */





extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170E54;
extern s32 D_80173CC4;

/* Updates directional movement, slows it, and settles the object onto its grid tile. */
void func_80172F14(S_80172F14_1 *controller, EntityRec *motion, Rec_D_80082E80 *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 speed_limit;
    s32 tracked_object;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;

    switch (controller->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) + direction * 2) << 19;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + direction * 2) << 19;
        controller->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(controller, motion, entity, &D_80173CC4);
            return;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }

        timer = 5;
        if (((EntityRec *)source)->flags1C & 0x228) {
            timer = 8;
        }
        controller->unk_96.s = timer;

        {
            s32 velocity = motion->unk_0C;
            motion->unk_0C = velocity - velocity / 4;
        }
        {
            s32 velocity = motion->unk_10;
            motion->unk_10 = velocity - velocity / 4;
        }
        /* fall through */

    case 1:
        speed_limit = 0x7FFF;
        {
            s32 velocity = motion->unk_0C;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->unk_0C = velocity -
                    (*(s16 *)((u8 *)((s8 *)dirStepX) + direction * 2) << 15);
            }
        }
        {
            s32 velocity = motion->unk_10;
            s32 magnitude = velocity;

            magnitude = abs(magnitude);
            if (speed_limit < magnitude) {
                motion->unk_10 = velocity -
                    (*(s16 *)((u8 *)((s8 *)dirStepY) + direction * 2) << 15);
            }
        }

        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
            goto check_timer;
        }
        if (entity->unk_14.at00_u16.v & 0x6000) {
            controller->unk_96.s = 0;
        }

        if (((EntityRec *)source)->unk_28 != 0) {
            {
                s32 tile_pos = entity->unk_24 << 6;
                s32 current_pos = motion->x.w.i - 0x20;

                motion->unk_0C = (tile_pos - current_pos) << 15;
            }
            {
                s32 tile_pos = entity->unk_25 << 6;
                s32 current_pos = motion->y.w.i - 0x20;

                motion->unk_10 = (tile_pos - current_pos) << 15;
            }
        } else {
            motion->unk_0C = 0;
            motion->unk_10 = 0;
        }

check_timer:
        if (controller->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->flags14 = 0;
            func_800AAA54(controller, motion, entity, &D_80173CC4);
            return;
        }
        controller->unk_96.s = 8;
        controller->unk_9B++;
        return;

    case 2:
        if (controller->unk_96.s != 0) {
            {
                s32 tile_pos = entity->unk_24 << 6;
                s32 current_pos = motion->x.w.i - 0x20;

                motion->unk_0C = (tile_pos - current_pos) << 16;
            }
            {
                s32 tile_pos = entity->unk_25 << 6;
                s32 current_pos = motion->y.w.i - 0x20;

                motion->unk_10 = (tile_pos - current_pos) << 16;
            }
        }

        timer = controller->unk_96.u - 1;
        controller->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, entity->unk_24,
                      entity->unk_25);

        tracked_object = ((s32)dungeonStatus.unk_10);
        if (tracked_object == (s32)((u8 *)source - 0x20)) {
            dungeonStatus.unk_10 = tracked_object & 0x7FFFFFFF;
        }
        controller->unk_8C = &D_80170E54;
        return;

    default:
        return;
    }
}
