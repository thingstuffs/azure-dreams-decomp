#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_801730B8_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801730B8_1;   /* arg0 in func_801730B8 */


typedef struct S_801730B8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801730B8_3;   /* arg2 in func_801730B8 */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern s32 D_80170E84;
extern s32 D_80174838;


/* Update directional movement, then stop or return to the destination tile. */
void func_801730B8(S_801730B8_1 *action, Rec_D_800E3D7C *motion, S_801730B8_3 *destination, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)source)->unk_6A.u >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C.n =
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 18;
        motion->unk_10.at00.v =
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 18;
        action->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            goto start_action;
        }
        if (destination->unk_14 & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_1C.s & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C.n -= motion->unk_0C.n / 4;
        motion->unk_10.at00.v -= motion->unk_10.at00.v / 4;
        /* fall through */

    case 1:
        motion->unk_0C.n -=
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 14;
        motion->unk_10.at00.v -=
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (destination->unk_14 & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->unk_14.s32 = 0;
        motion->unk_10.at00.v = 0;
        motion->unk_0C.n = 0;
        func_800AAA54(action, motion, destination, &D_80174838);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_x = destination->unk_24 << 6;
                s32 current_x = motion->unk_00.at02.v - 0x20;

                motion->unk_0C.n = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = destination->unk_25 << 6;
                s32 current_y = motion->unk_04.at02.v - 0x20;

                motion->unk_10.at00.v = ((target_y - current_y) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->unk_14.s32 = 0;
        motion->unk_10.at00.v = 0;
        motion->unk_0C.n = 0;
        func_800A2B04(motion, destination->unk_24, destination->unk_25);

        global_state = &D_80083460;
        tracked_entity = global_state[4];
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            global_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E84;
        return;

    default:
        return;
    }
}
