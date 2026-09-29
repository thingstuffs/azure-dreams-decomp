#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017380C_0;   /* arg0 in func_8017380C */






extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759C8[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

/* Updates a staged movement sequence and returns the entity to its tile. */
void func_8017380C(void *action, EntityRec *motion, void *entity, EntityRec *actor)
{
    s32 state;

    state = ((S_8017380C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(actor);
        ((S_8017380C_0 *)action)->unk_96.s = 4;
        ((S_8017380C_0 *)action)->unk_9B++;
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, entity, D_801759C8);
            return;
        }
        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            return;
        }
        ((S_8017380C_0 *)action)->unk_96.s = 0;
        ((S_8017380C_0 *)action)->unk_9B = 3;
        return;

    case 1:
        {
            s16 frames_left;

            frames_left = ((S_8017380C_0 *)action)->unk_96.u - 1;
            ((S_8017380C_0 *)action)->unk_96.s = frames_left;
            if (frames_left > 0) {
                motion->unk_0C =
                    *(s16 *)((u8 *)((s8 *)dirStepX) +
                        ((actor->unk_6A >> 8) & 0xE)) << 19;
                motion->unk_10 =
                    *(s16 *)((u8 *)((s8 *)dirStepY) +
                        ((actor->unk_6A >> 8) & 0xE)) << 19;
                return;
            }
            if (frames_left != 0) {
                return;
            }
            motion->unk_0C =
                *(s16 *)((u8 *)((s8 *)dirStepX) +
                    ((actor->unk_6A >> 8) & 0xE)) << 18;
            motion->unk_10 =
                *(s16 *)((u8 *)((s8 *)dirStepY) +
                    ((actor->unk_6A >> 8) & 0xE)) << 18;
            ((S_8017380C_0 *)action)->unk_96.s = 6;
            ((S_8017380C_0 *)action)->unk_9B++;
            return;
        }

    case 2:
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(action, motion, entity, D_801759C8);
            return;
        }
        {
            s16 return_frames;
            s32 origin_y;
            u16 previous_frames;

            return_frames = ((S_8017380C_0 *)action)->unk_96.s;
            if (return_frames != 0) {
                motion->unk_0C =
                    (((((Rec_D_80082E80 *)entity)->unk_24 << 6) - ({ motion->x.w.i - 0x20; })) << 16) / return_frames;
                origin_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    (((((Rec_D_80082E80 *)entity)->unk_25 << 6) - origin_y) << 16) /
                    ((S_8017380C_0 *)action)->unk_96.s;
            }
            previous_frames = ((S_8017380C_0 *)action)->unk_96.u;
            ((S_8017380C_0 *)action)->unk_96.s = previous_frames - 1;
            if ((s32)(previous_frames << 16) > 0) {
                return;
            }
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            ((S_8017380C_0 *)action)->unk_9B++;
            return;
        }

    case 3:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
        if (((Rec_D_80082E80 *)entity)->unk_2C.as_pv == D_80175998) {
            u8 *direction_table;

            direction_table = D_80175988;
            (*(void * *)((u8 *)entity + 0x2C)) = direction_table;
            func_80047784(entity,
                direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {
            s32 entity_ref;

            entity_ref = ((s32)dungeonStatus.unk_10);
            if (entity_ref == (s32)((u8 *)actor - 0x20)) {
                dungeonStatus.unk_10 = entity_ref & 0x7FFFFFFF;
            }
        }
        ((S_8017380C_0 *)action)->unk_8C = &D_801717F4;
        return;
    }
}
