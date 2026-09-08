#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8017345C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017345C_1;   /* arg0 in func_8017345C */




extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E94;
extern u8 D_80174ABC[];


/* Updates directional motion and returns the entity to its tile when the timer expires. */
void func_8017345C(S_8017345C_1 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, void *entity)
{
    s16 timer;
    s32 tracked_entity;
    s32 *global_state;
    s32 direction;

    direction = (((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 9) & 7;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C.as_s32 = ((s16 *)&D_8006CCD8)[direction] << 17;
        motion->unk_10.at00_s32.v = ((s16 *)&D_8006CCE8)[direction] << 17;
        action->unk_9B++;

        if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
            goto start_action;
        }
        if (tile->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C.as_s32 -= motion->unk_0C.as_s32 / 4;
        motion->unk_10.at00_s32.v -= motion->unk_10.at00_s32.v / 4;
        /* fall through */

    case 1:
        motion->unk_0C.as_s32 -=
            ((s16 *)&D_8006CCD8)[direction] << 14;
        motion->unk_10.at00_s32.v -=
            ((s16 *)&D_8006CCE8)[direction] << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800AAA54(action, motion, tile, D_80174ABC);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = tile->unk_24 << 6;
                s32 current_x = motion->unk_00.at02_s16.v - 0x20;
                motion->unk_0C.as_s32 =
                    ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = tile->unk_25 << 6;
                s32 current_y = motion->unk_04.at02_s16.v - 0x20;
                motion->unk_10.at00_s32.v =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, tile->unk_24,
                      tile->unk_25);

        global_state = &D_80083460;
        tracked_entity = global_state[4];
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            global_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E94;
        return;

    default:
        return;
    }
}
