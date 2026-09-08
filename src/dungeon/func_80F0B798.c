#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F98_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F98_0;   /* arg0 in func_80172F98 */






typedef struct {
    u8 pad00[0x10];
    s32 field10;
} D_80083460_t;

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern D_80083460_t D_80083460;
extern u8 D_80170F74[];
extern u8 D_80173D60[];

/* Updates directional movement and returns the entity to its target tile. */
void func_80172F98(S_80172F98_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *target, void *entity)
{
    s16 return_timer;
    s16 next_timer;
    s16 initial_timer;
    s32 velocity_y;
    s32 direction;
    s32 velocity_x;
    s32 biased_x;
    s32 biased_y;
    s32 target_x;
    s32 origin_x;
    s32 target_y;
    s32 origin_y;
    u8 state;

    state = action->unk_9B;
    direction = (((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 9) & 7;

    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    default:
        goto end;
    }

state_0:
    func_800AD4D0(entity);
    motion->unk_0C.as_s32 =
        ((s16 *)&D_8006CCD8)[direction] << 16;
    motion->unk_10.at00_s32.v =
        ((s16 *)&D_8006CCE8)[direction] << 16;
    action->unk_9B++;

    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        goto reset_and_start;
    }
    if (target->unk_14.at00_u16.v & 0x8000) {
        action->unk_96.s = 0;
        action->unk_9B = 2;
        goto end;
    }

    initial_timer = -1;
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x228) {
        initial_timer = 8;
    }
    action->unk_96.s = initial_timer;

    velocity_x = motion->unk_0C.as_s32;
    biased_x = velocity_x;
    if (velocity_x < 0) {
        biased_x = velocity_x + 3;
    }
    motion->unk_0C.as_s32 = velocity_x - (biased_x >> 2);

    velocity_y = motion->unk_10.at00_s32.v;
    biased_y = velocity_y;
    if (velocity_y < 0) {
        biased_y = velocity_y + 3;
    }
    motion->unk_10.at00_s32.v = velocity_y - (biased_y >> 2);

state_1:
    motion->unk_0C.as_s32 -=
        ((s16 *)&D_8006CCD8)[direction] << 13;
    motion->unk_10.at00_s32.v -=
        ((s16 *)&D_8006CCE8)[direction] << 13;

    if (action->unk_96.s > 0) {
        action->unk_96.u = action->unk_96.u - 1;
        goto timer_done;
    }
    if (target->unk_14.at00_u16.v & 0x6000) {
        action->unk_96.s = 0;
    }

timer_done:
    if (action->unk_96.s != 0) {
        goto end;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
        goto continue_state;
    }

reset_and_start:
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800AAA54(action, motion, target, D_80173D60);
    goto end;

continue_state:
    action->unk_96.s = 8;
    action->unk_9B++;
    goto end;

state_2:
    return_timer = action->unk_96.s;
    if (return_timer != 0) {
        target_x = target->unk_24 << 6;
        origin_x = motion->unk_00.at02_s16.v - 0x20;
        motion->unk_0C.as_s32 =
            ((target_x - origin_x) << 15) / return_timer;
        target_y = target->unk_25 << 6;
        origin_y = motion->unk_04.at02_s16.v - 0x20;
        motion->unk_10.at00_s32.v =
            ((target_y - origin_y) << 15) /
            action->unk_96.s;
    }

    next_timer = action->unk_96.u - 1;
    action->unk_96.u = next_timer;
    if (next_timer > 0) {
        goto end;
    }

    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, target->unk_24, target->unk_25);

    if (D_80083460.field10 == (s32)entity - 0x20) {
        D_80083460.field10 &= 0x7FFFFFFF;
    }
    action->unk_8C = D_80170F74;

end:
    return;
}

/* MECHANISM: The natural long-lived arguments preserve the retail 0x28 frame and s1/s0/s2/s3/s4 roles.
   Typed s16 array indexing materializes each table base before its direction shift.
   Split expression-form s32 coordinate temps block fold reassociation and schedule the second lh over the first divide result. */
