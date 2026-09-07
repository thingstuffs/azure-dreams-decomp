#include "common.h"

typedef struct S_801732B4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_801732B4_0;   /* arg3 in func_801732B4 */

typedef struct S_801732B4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801732B4_1;   /* arg0 in func_801732B4 */

typedef struct S_801732B4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801732B4_2;   /* arg1 in func_801732B4 */

typedef struct S_801732B4_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801732B4_3;   /* arg2 in func_801732B4 */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern s32 D_80170F6C;
extern s32 D_80175268;


/* Updates directional motion, then recenters the entity on its tile and finishes the action. */
void func_801732B4(S_801732B4_1 *action, S_801732B4_2 *motion, S_801732B4_3 *tile, void *entity)
{
    s16 timer;
    s32 tracked_entity;
    s32 *world_state;
    s32 direction;

    direction = (((S_801732B4_0 *)entity)->unk_6A >> 9) & 7;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C = ((s16 *)&D_8006CCD8)[direction] << 17;
        motion->unk_10 = ((s16 *)&D_8006CCE8)[direction] << 17;
        action->unk_9B++;

        if (((S_801732B4_0 *)entity)->unk_28 == 0) {
            goto start_action;
        }
        if (tile->unk_14 & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((S_801732B4_0 *)entity)->unk_1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;

        motion->unk_0C -= motion->unk_0C / 4;
        motion->unk_10 -= motion->unk_10 / 4;
        /* fall through */

    case 1:
        motion->unk_0C -= ((s16 *)&D_8006CCD8)[direction] << 14;
        motion->unk_10 -= ((s16 *)&D_8006CCE8)[direction] << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile->unk_14 & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((S_801732B4_0 *)entity)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, tile, &D_80175268);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_x;
                s32 current_x;

                target_x = tile->unk_24 << 6;
                current_x = motion->unk_02 - 0x20;
                motion->unk_0C =
                    ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_z;
                s32 current_z;

                target_z = tile->unk_25 << 6;
                current_z = motion->unk_06 - 0x20;
                motion->unk_10 =
                    ((target_z - current_z) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, tile->unk_24, tile->unk_25);

        world_state = &D_80083460;
        tracked_entity = world_state[4];
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            world_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170F6C;
        return;

    default:
        return;
    }
}
