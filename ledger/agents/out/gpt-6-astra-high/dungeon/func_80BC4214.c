#include "common.h"

typedef struct S_80173A14_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173A14_0;   /* arg0 in func_80173A14 */

typedef struct S_80173A14_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173A14_1;   /* arg1 in func_80173A14 */

typedef struct S_80173A14_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_80173A14_2;   /* arg3 in func_80173A14 */

typedef struct S_80173A14_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173A14_3;   /* arg2 in func_80173A14 */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s32 D_80083460;
extern s32 D_801719DC;
extern s32 D_8017466C;


/* Advance the action delay, reset motion, and select the next handler. */
void func_80173A14(S_80173A14_0 *action, S_80173A14_1 *motion, S_80173A14_3 *action_info, void *actor_data)
{
    s16 delay;
    s32 tracked_actor;
    s32 *global_state;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(actor_data);
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        action->unk_9B++;

        if (((S_80173A14_2 *)actor_data)->unk_28 == 0) {
            goto start_action;
        }
        if (action_info->unk_14 & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((S_80173A14_2 *)actor_data)->unk_1C & 0x228) {
            delay = 8;
        } else {
            delay = -1;
        }
        action->unk_96.s = delay;
        /* fall through */

    case 1:
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (action_info->unk_14 & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((S_80173A14_2 *)actor_data)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, action_info, &D_8017466C);
        return;

increment_state:
        action->unk_96.s = 2;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        delay = action->unk_96.u - 1;
        action->unk_96.s = delay;
        if ((s32)(delay << 16) > 0) {
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, action_info->unk_24, action_info->unk_25);

        global_state = &D_80083460;
        tracked_actor = global_state[4];
        if (tracked_actor == (s32)((u8 *)actor_data - 0x20)) {
            global_state[4] = tracked_actor & 0x7FFFFFFF;
        }
        action->unk_8C = &D_801719DC;
        return;

    default:
        return;
    }
}
