#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in func_80172EF4 */





extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80170E5C[];
extern u8 D_80173D0C[];
extern s32 D_80173D24;

/* Apply directional movement, slow it down, and return the actor to its tile center. */
void func_80172EF4(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s16 timer;
    s16 *x_steps;
    s16 *y_step;
    s32 direction;
    s32 initial_step_offset;
    s32 velocity_x;
    s32 velocity_y;
    s32 brake_step_offset;
    s32 biased_velocity_x;
    s32 biased_velocity_y;
    s32 target_x;
    s32 offset_x;
    s32 target_y;
    s32 offset_y;
    s32 actor_ref;

    direction = (actor->unk_6A >> 9) & 7;

    switch (((S_80172EF4_1 *)action)->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        x_steps = (s16 *)((s8 *)dirStepX);
        initial_step_offset = direction * 2;
        motion->unk_0C =
            *(s16 *)((u8 *)x_steps + initial_step_offset) << 0x12;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) + initial_step_offset) << 0x12;
        ((S_80172EF4_1 *)action)->unk_9B++;

        if (actor->unk_28 == 0) {
            goto start_action;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
            ((S_80172EF4_1 *)action)->unk_9B = 2;
            return;
        }

        timer = -1;
        if (actor->flags1C & 0x228) {
            timer = 8;
        }
        ((S_80172EF4_1 *)action)->unk_96.s = timer;

        velocity_x = motion->unk_0C;
        biased_velocity_x = velocity_x;
        if (velocity_x < 0) {
            biased_velocity_x = velocity_x + 3;
        }
        velocity_y = motion->unk_10;
        motion->unk_0C = velocity_x - (biased_velocity_x >> 2);
        biased_velocity_y = velocity_y;
        if (velocity_y < 0) {
            biased_velocity_y = velocity_y + 3;
        }
        motion->unk_10 = velocity_y - (biased_velocity_y >> 2);
        /* fall through */

    case 1:
        x_steps = (s16 *)((s8 *)dirStepX);
        brake_step_offset = direction * 2;
        y_step = (s16 *)((u8 *)((s8 *)dirStepY) + brake_step_offset);
        motion->unk_0C -=
            *(s16 *)((u8 *)x_steps + brake_step_offset) << 0xF;
        motion->unk_10 -= *y_step << 0xF;

        if (((S_80172EF4_1 *)action)->unk_96.s > 0) {
            ((S_80172EF4_1 *)action)->unk_96.s = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
        }
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (actor->unk_28 != 0) {
            goto increment_state;
        }

start_action:
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(action, motion, sprite, &D_80173D24);
        return;

increment_state:
        ((S_80172EF4_1 *)action)->unk_96.s = 4;
        ((S_80172EF4_1 *)action)->unk_9B++;
        return;

    case 2:
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            offset_x = motion->x.w.i - 0x20;
            motion->unk_0C = (target_x - offset_x) << 0x10 >> 1;
            target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            offset_y = motion->y.w.i - 0x20;
            motion->unk_10 = (target_y - offset_y) << 0x10 >> 1;
        }

        timer = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        ((S_80172EF4_1 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173D0C;
        func_80047784(sprite,
            D_80173D0C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        actor_ref = ((s32)dungeonStatus.unk_10);
        if (actor_ref == (s32)((u8 *)actor - 0x20)) {
            dungeonStatus.unk_10 = actor_ref & 0x7FFFFFFF;
        }
        ((S_80172EF4_1 *)action)->unk_8C = D_80170E5C;
        return;

    default:
        return;
    }
}
