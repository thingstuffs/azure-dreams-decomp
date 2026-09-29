#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8014F234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8014F234_0;   /* arg0 in func_8014F234 */





extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_8014CE7C;
extern u8 D_80150C44[];
extern u8 D_80150C74[];

/* Updates directional motion and animation, then settles the entity at its tile center. */
void func_8014F234(void *controller, EntityRec *motion, void *sprite, EntityRec *entity)
{
    s32 state;
    s16 timer;
    s32 tracked_entity;

    state = ((S_8014F234_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C =
            -((s16 *)((s8 *)dirStepX))[(entity->unk_6A >> 9) & 7] << 15;
        motion->unk_10 =
            -((s16 *)((s8 *)dirStepY))[(entity->unk_6A >> 9) & 7] << 15;
        ((S_8014F234_0 *)controller)->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(controller, motion, sprite, D_80150C74);
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_8014F234_0 *)controller)->unk_96.s = 0;
            ((S_8014F234_0 *)controller)->unk_9B = 3;
            return;
        }

        if (((u32)entity->flags1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_8014F234_0 *)controller)->unk_96.s = timer;

        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;

    case 1:
        motion->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(entity->unk_6A >> 9) & 7] << 14;
        motion->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(entity->unk_6A >> 9) & 7] << 14;

        if (((S_8014F234_0 *)controller)->unk_96.s > 0) {
            ((S_8014F234_0 *)controller)->unk_96.s = ((S_8014F234_0 *)controller)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_8014F234_0 *)controller)->unk_96.s = 0;
        }

        if (((S_8014F234_0 *)controller)->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(controller, motion, sprite, D_80150C74);
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150C44;
        func_80047784(
            sprite,
            D_80150C44[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((S_8014F234_0 *)controller)->unk_9B++;
        return;
    case 2:
            motion->unk_0C +=
                ((s16 *)((s8 *)dirStepX))[(entity->unk_6A >> 9) & 7] << 14;
            motion->unk_10 +=
                ((s16 *)((s8 *)dirStepY))[(entity->unk_6A >> 9) & 7] << 14;
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
                return;
            }

            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150C44;
            func_80047784(
                sprite,
                D_80150C44[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            ((S_8014F234_0 *)controller)->unk_96.s = 8;
            ((S_8014F234_0 *)controller)->unk_9B++;
            return;
    case 3:
            timer = ((S_8014F234_0 *)controller)->unk_96.s;
            if (timer != 0) {
                {
                    s32 tile_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                    s32 offset_x = motion->x.w.i - 0x20;
                    motion->unk_0C = ((tile_x - offset_x) << 15) / timer;
                }
                {
                    s32 tile_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                    s32 offset_y = motion->y.w.i - 0x20;
                    motion->unk_10 =
                        ((tile_y - offset_y) << 15) / ((S_8014F234_0 *)controller)->unk_96.s;
                }
            }

            timer = ((S_8014F234_0 *)controller)->unk_96.u - 1;
            ((S_8014F234_0 *)controller)->unk_96.s = timer;
            if ((s32)(timer << 16) > 0) {
                return;
            }

            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            motion->x.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
            motion->y.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

            tracked_entity = ((s32)dungeonStatus.unk_10);
            if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
                dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
            }
            ((S_8014F234_0 *)controller)->unk_8C = &D_8014CE7C;

            return;
    default:
        return;
    }
}
