#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F98_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F98_0;   /* arg0 in func_80172F98 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170F74[];
extern u8 D_80173D60[];

/* Updates directional movement and returns the entity to its target tile. */
void func_80172F98(S_80172F98_0 *action, EntityRec *motion, Rec_D_80082E80 *target, void *entity)
{
    s16 return_timer;
    s16 next_timer;
    s16 initial_timer;
    s32 velocity_y;
    s32 direction;
    s32 velocity_x;
    s32 biased_x;
    s32 biased_y;
    s32 target_x;
    s32 origin_x;
    s32 target_y;
    s32 origin_y;
    u8 state;

    state = action->unk_9B;
    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;

    switch (state) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C =
            ((s16 *)((s8 *)dirStepX))[direction] << 16;
        motion->unk_10 =
            ((s16 *)((s8 *)dirStepY))[direction] << 16;
        action->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, target, D_80173D60);
            return;
        }
        if (target->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }

        initial_timer = -1;
        if (((u32)((EntityRec *)entity)->flags1C) & 0x228) {
            initial_timer = 8;
        }
        action->unk_96.s = initial_timer;

        velocity_x = motion->unk_0C;
        biased_x = velocity_x;
        motion->unk_0C = velocity_x - (biased_x / 4);

        velocity_y = motion->unk_10;
        biased_y = velocity_y;
        motion->unk_10 = velocity_y - (biased_y / 4);

    case 1:
        motion->unk_0C -=
            ((s16 *)((s8 *)dirStepX))[direction] << 13;
        motion->unk_10 -=
            ((s16 *)((s8 *)dirStepY))[direction] << 13;

        if (action->unk_96.s > 0) {
            action->unk_96.u = action->unk_96.u - 1;
        } else if (target->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }

        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, target, D_80173D60);
        } else {
            action->unk_96.s = 8;
            action->unk_9B++;
        }
        return;

    case 2:
        return_timer = action->unk_96.s;
        if (return_timer != 0) {
            target_x = target->unk_24 << 6;
            origin_x = motion->x.w.i - 0x20;
            motion->unk_0C =
                ((target_x - origin_x) << 15) / return_timer;
            target_y = target->unk_25 << 6;
            origin_y = motion->y.w.i - 0x20;
            motion->unk_10 =
                ((target_y - origin_y) << 15) /
                action->unk_96.s;
        }

        next_timer = action->unk_96.u - 1;
        action->unk_96.u = next_timer;
        if (next_timer > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, target->unk_24, target->unk_25);

        if (((s32)dungeonStatus.unk_10) == (s32)entity - 0x20) {
            *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
        }
        action->unk_8C = D_80170F74;

        return;
    default:
        return;
    }
}

/* MECHANISM: The natural long-lived arguments preserve the retail 0x28 frame and s1/s0/s2/s3/s4 roles.
   Typed s16 array indexing materializes each table base before its direction shift.
   Split expression-form s32 coordinate temps block fold reassociation and schedule the second lh over the first divide result. */
