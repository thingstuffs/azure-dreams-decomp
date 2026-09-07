#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172FE4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FE4_0;   /* arg0 in func_80172FE4 */





extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170EA8;
extern s32 D_80174068;


/* Updates directional movement, then stops or returns the entity to its grid position. */
void func_80172FE4(S_80172FE4_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *entity, void *source)
{
    s16 timer;
    s32 current_x;
    s32 current_y;
    s32 target_x;
    s32 tracked_addr;
    s32 *tracking_state;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(source);
        motion->unk_0C.as_s32 =
            -*(s16 *)((u8 *)&D_8006CCD8 +
                      ((((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 8) & 0xE)) << 15;
        motion->unk_10.at00_s32.v =
            -*(s16 *)((u8 *)&D_8006CCE8 +
                      ((((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 8) & 0xE)) << 15;
        action->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            goto start_action;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->unk_0C.as_s32 -= motion->unk_0C.as_s32 / 4;
        motion->unk_10.at00_s32.v -= motion->unk_10.at00_s32.v / 4;
        /* fall through */

    case 1:
        motion->unk_0C.as_s32 +=
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 8) & 0xE)) << 14;
        {
            s32 table_offset;
            u8 *y_table;

            y_table = (u8 *)&D_8006CCE8;
            table_offset = (((Rec_D_800E3D7C *)source)->unk_6A.as_u16 >> 8) & 0xE;
            ASM_KEEP(table_offset);   /* MATCH pin: retail delay-slot fill depends on it */
            motion->unk_10.at00_s32.v +=
                *(s16 *)(y_table + table_offset) << 14;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
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
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800AAA54(action, motion, entity, &D_80174068);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            target_x = entity->unk_24 << 6;
            current_x = motion->unk_00.at02_s16.v - 0x20;
            current_y = motion->unk_04.at02_s16.v - 0x20;
            motion->unk_0C.as_s32 =
                ((target_x - current_x) << 15) /
                action->unk_96.s;
            motion->unk_10.at00_s32.v =
                (((entity->unk_25 << 6) - current_y) << 15) /
                action->unk_96.s;
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        tracking_state = &D_80083460;
        tracked_addr = tracking_state[4];
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            tracking_state[4] = tracked_addr & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170EA8;
        return;

    default:
        return;
    }
}
