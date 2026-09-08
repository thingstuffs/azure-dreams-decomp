#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172CE0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172CE0_0;   /* arg0 in func_80172CE0 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern s32 D_80171058;
extern s32 D_801748C0;

/* Applies backward motion, then returns the actor to its tile center or starts the next action. */
void func_80172CE0(S_80172CE0_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *entity, void *actor)
{
    s16 frames_left;
    s32 tracked_actor;
    s32 *global_state;

    switch (action->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        motion->unk_0C.as_s32 =
            -*(s16 *)(&D_8006CCD8 +
                (((u16)((Rec_D_800E3D7C *)actor)->unk_6A.as_s16 >> 8) & 0xE)) << 15;
        motion->unk_10.at00_s32.v =
            -*(s16 *)(&D_8006CCE8 +
                (((u16)((Rec_D_800E3D7C *)actor)->unk_6A.as_s16 >> 8) & 0xE)) << 15;
        action->unk_9B++;

        if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
            goto start_action;
        }
        if (entity->unk_14.at00_u16.v & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x228) {
            frames_left = 8;
        } else {
            frames_left = -1;
        }
        action->unk_96.s = frames_left;
        motion->unk_0C.as_s32 -= motion->unk_0C.as_s32 / 4;
        motion->unk_10.at00_s32.v -= motion->unk_10.at00_s32.v / 4;

    case 1:
        motion->unk_0C.as_s32 +=
            *(s16 *)(&D_8006CCD8 +
                (((u16)((Rec_D_800E3D7C *)actor)->unk_6A.as_s16 >> 8) & 0xE)) << 10;
        {
            register s32 direction_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            direction_offset = ((u16)((Rec_D_800E3D7C *)actor)->unk_6A.as_s16 >> 8) & 0xE;
            motion->unk_10.at00_s32.v +=
                *(s16 *)(&D_8006CCE8 + direction_offset) << 10;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->unk_14.at00_u16.v & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800AAA54(action, motion, entity, &D_801748C0);
        return;

increment_state:
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        frames_left = action->unk_96.s;
        if (frames_left != 0) {
            {
                s32 target_x = entity->unk_24 << 6;
                s32 current_x = motion->unk_00.at02_s16.v - 0x20;

                motion->unk_0C.as_s32 =
                    ((target_x - current_x) << 15) / frames_left;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->unk_04.at02_s16.v - 0x20;

                motion->unk_10.at00_s32.v =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
            }
        }
        frames_left = action->unk_96.u - 1;
        action->unk_96.s = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            return;
        }
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, entity->unk_24, entity->unk_25);

        global_state = &D_80083460;
        tracked_actor = global_state[4];
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            global_state[4] = tracked_actor & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80171058;
        return;

    default:
        return;
    }
}
