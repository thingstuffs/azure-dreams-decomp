#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173964_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173964_0;   /* arg0 in func_80173964 */






extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174DFC[];
extern u8 D_80174E24[];

/* Applies a brief directional movement, then returns the actor to its grid position. */
void func_80173964(void *action, void *motion, void *actor, void *entity)
{
    s32 state;
    s16 timer;
    u16 timer_bits;
    u8 next_state;
    s32 target_x;
    s32 current_x;
    s32 target_y;
    s32 current_y;
    s32 tracked_entity;

    state = ((S_80173964_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(entity);
    ((S_80173964_0 *)action)->unk_96.s = 12;
    ((S_80173964_0 *)action)->unk_9B++;
    if (((EntityRec *)entity)->unk_28 == 0) {
        goto initialize;
    }
    if (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000) {
        ((S_80173964_0 *)action)->unk_96.s = 0;
        ((S_80173964_0 *)action)->unk_9B = 3;
    }
    goto done;

state_1:
    timer_bits = ((S_80173964_0 *)action)->unk_96.u - 1;
    ((S_80173964_0 *)action)->unk_96.u = timer_bits;
    timer = timer_bits;
    if (timer >= 11) {
        ((EntityRec *)motion)->unk_0C =
            *(s16 *)((u8 *)((s8 *)dirStepX) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 20;
        ((EntityRec *)motion)->unk_10 =
            *(s16 *)((u8 *)((s8 *)dirStepY) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 20;
        ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x800;
        goto done;
    }
    if (timer >= 7) {
        ((EntityRec *)motion)->unk_0C /= 4;
        ((EntityRec *)motion)->unk_10 /= 4;
        goto done;
    }
    if (timer >= 2) {
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        goto done;
    }
    if (timer == state) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v &= 0xF7FF;
        goto done;
    }
    if (timer != 0) {
        goto done;
    }
    next_state = ((S_80173964_0 *)action)->unk_9B;
    timer = 4;
    ((S_80173964_0 *)action)->unk_96.s = timer;
    goto increment_state;

state_2:
    if (((EntityRec *)entity)->unk_28 != 0) {
        goto calculate;
    }

initialize:
    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    func_800AAA54(action, motion, actor, D_80174E24);
    goto done;

calculate:
    timer = ((S_80173964_0 *)action)->unk_96.s;
    if (timer != 0) {
        target_x = ((Rec_D_80082E80 *)actor)->unk_24 << 6;
        current_x = ((EntityRec *)motion)->x.w.i - 0x20;
        ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / timer;
        target_y = ((Rec_D_80082E80 *)actor)->unk_25 << 6;
        current_y = ((EntityRec *)motion)->y.w.i - 0x20;
        ((EntityRec *)motion)->unk_10 =
            ((target_y - current_y) << 16) / ((S_80173964_0 *)action)->unk_96.s;
    }
    timer_bits = ((S_80173964_0 *)action)->unk_96.u;
    ((S_80173964_0 *)action)->unk_96.u = timer_bits - 1;
    if ((s32)(timer_bits << 16) > 0) {
        goto done;
    }
    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    next_state = ((S_80173964_0 *)action)->unk_9B;

increment_state:
    ((S_80173964_0 *)action)->unk_9B = next_state + 1;
    goto done;

state_3:
    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
    if (((Rec_D_80082E80 *)actor)->unk_2C.as_pv == D_80174DFC) {
        (*(void * *)((u8 *)actor + 0x2C)) = D_80174DEC;
        func_80047784(
            actor,
            D_80174DEC[((gameWork.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
    }
    tracked_entity = ((s32)dungeonStatus.unk_10);
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
    }
    ((S_80173964_0 *)action)->unk_8C = &D_80171728;

done:
    return;
}

/* MECHANISM: Four live arguments naturally produce the 0x28 frame and s1/s0/s2/s3 save roles.
   A distinct u8 next_state plus timer-held constant 4 fixes v0/v1 lifetimes and the bgtz store slot.
   The named D_80083460 pointer forces retail's split lui/addiu base before the final field load. */
