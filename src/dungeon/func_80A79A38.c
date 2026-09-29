#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8016D238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8016D238_1;   /* arg0 in func_8016D238 */




extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_8016AE54;
extern u8 D_8016E150[];
extern u8 D_8016E178[];

/* Updates directional motion and settles the actor at its tile center. */
void func_8016D238(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_actor;

    direction = (actor->unk_6A >> 9) & 7;
    state = ((S_8016D238_1 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    return;

state_zero:
    func_800AD4D0(actor);
    motion->unk_0C = ((s16 *)((s8 *)dirStepX))[direction] << 18;
    motion->unk_10 = ((s16 *)((s8 *)dirStepY))[direction] << 18;
    ((S_8016D238_1 *)action)->unk_9B++;

    if (actor->unk_28 == 0) {
        goto stop_motion;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_8016D238_1 *)action)->unk_96.s = 0;
        ((S_8016D238_1 *)action)->unk_9B = 3;
        return;
    }

    if (((u32)actor->flags1C) & 0x228) {
        timer = 8;
    } else {
        timer = -1;
    }
    ((S_8016D238_1 *)action)->unk_96.s = timer;

    motion->unk_0C -= motion->unk_0C / 4;
    motion->unk_10 -= motion->unk_10 / 4;

state_one:
    motion->unk_0C -= ((s16 *)((s8 *)dirStepX))[direction] << 14;
    motion->unk_10 -= ((s16 *)((s8 *)dirStepY))[direction] << 14;

    if (((S_8016D238_1 *)action)->unk_96.s > 0) {
        ((S_8016D238_1 *)action)->unk_96.s = ((S_8016D238_1 *)action)->unk_96.u - 1;
    } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((S_8016D238_1 *)action)->unk_96.s = 0;
    }

    if (((S_8016D238_1 *)action)->unk_96.s != 0) {
        return;
    }
    if (actor->unk_28 != 0) {
        goto continue_state_one;
    }

stop_motion:
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800AAA54(action, motion, sprite, D_8016E178);
    return;

continue_state_one:
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016E150;
    func_80047784(
        sprite,
        D_8016E150[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((S_8016D238_1 *)action)->unk_9B++;
    return;

state_two:
    motion->unk_0C -= ((s16 *)((s8 *)dirStepX))[direction] << 14;
    motion->unk_10 -= ((s16 *)((s8 *)dirStepY))[direction] << 14;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        return;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016E150;
    func_80047784(
        sprite,
        D_8016E150[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((S_8016D238_1 *)action)->unk_96.s = 8;
    ((S_8016D238_1 *)action)->unk_9B++;
    return;

state_three:
    timer = ((S_8016D238_1 *)action)->unk_96.s;
    if (timer != 0) {
        {
            s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            s32 current_x = motion->x.w.i - 0x20;
            motion->unk_0C = ((target_x - current_x) << 15) / timer;
        }
        {
            s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            s32 current_y = motion->y.w.i - 0x20;
            motion->unk_10 =
                ((target_y - current_y) << 15) / ((S_8016D238_1 *)action)->unk_96.s;
        }
    }

    timer = ((S_8016D238_1 *)action)->unk_96.u - 1;
    ((S_8016D238_1 *)action)->unk_96.s = timer;
    if ((s32)(timer << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    motion->x.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
    motion->y.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    tracked_actor = ((s32)dungeonStatus.unk_10);
    if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
        dungeonStatus.unk_10 = tracked_actor & 0x7FFFFFFF;
    }
    ((S_8016D238_1 *)action)->unk_8C = &D_8016AE54;

    return;
}
