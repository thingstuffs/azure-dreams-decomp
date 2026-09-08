#include "common.h"
#include "records/Rec_D_800E3D7C.h"
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

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
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
    s32 *entity_globals;

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
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
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
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 20;
        ((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v |= 0x800;
        goto done;
    }
    if (timer >= 7) {
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 /= 4;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v /= 4;
        goto done;
    }
    if (timer >= 2) {
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
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
    if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
        goto calculate;
    }

initialize:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800AAA54(action, motion, actor, D_80174E24);
    goto done;

calculate:
    timer = ((S_80173964_0 *)action)->unk_96.s;
    if (timer != 0) {
        target_x = ((Rec_D_80082E80 *)actor)->unk_24 << 6;
        current_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - current_x) << 16) / timer;
        target_y = ((Rec_D_80082E80 *)actor)->unk_25 << 6;
        current_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            ((target_y - current_y) << 16) / ((S_80173964_0 *)action)->unk_96.s;
    }
    timer_bits = ((S_80173964_0 *)action)->unk_96.u;
    ((S_80173964_0 *)action)->unk_96.u = timer_bits - 1;
    if ((s32)(timer_bits << 16) > 0) {
        goto done;
    }
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    next_state = ((S_80173964_0 *)action)->unk_9B;

increment_state:
    ((S_80173964_0 *)action)->unk_9B = next_state + 1;
    goto done;

state_3:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)actor)->unk_24, ((Rec_D_80082E80 *)actor)->unk_25);
    if (((Rec_D_80082E80 *)actor)->unk_2C.as_pv == D_80174DFC) {
        (*(void * *)((u8 *)actor + 0x2C)) = D_80174DEC;
        func_80047784(
            actor,
            D_80174DEC[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }
    entity_globals = &D_80083460;
    tracked_entity = entity_globals[4];
    if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
        entity_globals[4] = tracked_entity & 0x7FFFFFFF;
    }
    ((S_80173964_0 *)action)->unk_8C = &D_80171728;

done:
    return;
}

/* MECHANISM: Four live arguments naturally produce the 0x28 frame and s1/s0/s2/s3 save roles.
   A distinct u8 next_state plus timer-held constant 4 fixes v0/v1 lifetimes and the bgtz store slot.
   The named D_80083460 pointer forces retail's split lui/addiu base before the final field load. */
