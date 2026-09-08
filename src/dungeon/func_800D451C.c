#include "common.h"
#include "records/Rec_D_800E3D7C.h"
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

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_800D8C64[];
extern u8 D_8017586C[];
extern u8 D_8017588C[];


/* Updates directional movement, decelerates it, and settles the entity at its tile. */
void func_800D9C7C(S_800D9C7C_1 *controller, Rec_D_800E3D7C *motion, Rec_D_80082E80 *entity, void *source)
{
    s16 ticks_left;
    s32 direction;
    s32 tracked_entity;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 9) & 7;
    switch (controller->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 18;
        motion->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 18;
        controller->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            motion->unk_14.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
            motion->unk_0C.as_s32 = 0;
            func_800AAA54(controller, motion, entity, 0);
            return;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            controller->unk_96.s = 0;
            controller->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_1C.as_s32 & 0x228) {
            ticks_left = 8;
        } else {
            ticks_left = -1;
        }
        controller->unk_96.s = ticks_left;
        motion->unk_0C.as_s32 -= motion->unk_0C.as_s32 / 4;
        motion->unk_10.at00_s32.v -= motion->unk_10.at00_s32.v / 4;
        /* fall through */

    case 1:
        motion->unk_0C.as_s32 -=
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 14;
        motion->unk_10.at00_s32.v -=
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 14;
        if (controller->unk_96.s > 0) {
            controller->unk_96.s = controller->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
            controller->unk_96.s = 0;
        }
        if (controller->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_28 != 0) {
            goto increment_state;
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
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
                s32 current_x = motion->unk_00.at02_s16.v - 0x20;

                motion->unk_0C.as_s32 = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->unk_04.at02_s16.v - 0x20;

                motion->unk_10.at00_s32.v = ((target_y - current_y) << 15) >> 1;
            }
        }
        ticks_left = controller->unk_96.u - 1;
        controller->unk_96.s = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        global_state = &D_80083460;
        tracked_entity = global_state[4];
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            global_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        controller->unk_8C = D_800D8C64;
        return;

    default:
        return;
    }
}
