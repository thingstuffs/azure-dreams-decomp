#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3s;

typedef struct {
    u8 pad0[0x30];
    s16 x;
    s16 y;
    s16 z;
    u8 pad36[2];
    s16 cur_x;
    s16 cur_y;
    s16 cur_z;
    u8 pad3e[0xA];
    s16 state;
    u8 pad4a[2];
    s16 timer;
    u8 pad4e[2];
    s16 phase;
    u8 pad52[2];
    s16 step;
} State;

typedef struct {
    u8 pad0[2];
    s16 cur_x;
    u8 pad4[2];
    s16 cur_y;
    u8 pad8[2];
    s16 cur_z;
    u8 intensity;
    u8 padD;
    s16 x;
    u8 pad10[2];
    s16 y;
    u8 pad14[2];
    s16 z;
} Target;

typedef struct S_func_819615E4_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_func_819615E4_0;

typedef struct S_func_819615E4_1 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
} S_func_819615E4_1;

typedef struct S_func_819615E4_2 {
    u8 pad_00[0x2A];
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_2A;
    u8 pad_2C[0x5C];
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_88;
} S_func_819615E4_2;

typedef struct S_func_819615E4_3 {
    void *unk_00;
} S_func_819615E4_3;

typedef struct S_func_819615E4_4 {
    u8 pad_00[8];
    void *unk_08;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 unk_25;
} S_func_819615E4_4;

typedef struct S_func_819615E4_5 {
    s16 unk_00;
} S_func_819615E4_5;

typedef struct S_func_819615E4_6 {
    s16 unk_00;
} S_func_819615E4_6;

extern u16 D_80027330[];
extern void **D_800E3D18;

extern void func_80025334(s16, s16, s16);
extern void func_8003DE58(void *, void *, Vec3s *, s16);
extern void func_800B8D64(s16, s16, s16);

/* Interpolate the target position, fade its color, and finish the transition. */
/* MECHANISM: state->state selects with a switch, cases 0..3 laid out in source order so the
   dispatch tree's last `beq ==3` is followed by case 0's body (an if-chain puts case 3's body
   right after the default jump and jump.c inverts the test).  case 0 falls through into case 1.
   The `j 0x271ec` sites are the switch's end-of-switch edge = `return`; the `j 0x2711c` from
   case 1 ends with the same `state->state = value + 1; return` tail as case 2 (written out
   in both arms), and case 2's step != 0 path repeats case 3's flag-setting tail.  The 0x80080000 page plus 0x2E80 is the symbol D_80082E80,
   which is what frees the $2 pin; one u16 carrying the 5 and the 4 keeps the join value in v0. */
void func_819615E4(State *state, Target *target, S_func_819615E4_0 *color)
{
    Vec3s position_offset;
    Vec3s position;
    s32 distance;
    s32 current_coord;
    s16 smoothed_coord;
    u16 phase_value;
    u16 const_reg;

    D_80027330[0]++;

    switch (state->state) {
    case 0:
    {
        s32 transform_offset;

        position.x = ((u16)D_80083780.x.w.i);
        position.y = ((u16)D_80083780.y.w.i);
        position.z = ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_88.u16_value - 0x50;
        transform_offset = ((gameWork.view.viewAngle + ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_2A.s16_value + 0x100) >> 7) & 0x1C;
        func_8003DE58(((S_func_819615E4_3 *)((s32)transform_offset + (s32)D_800E3D18))->unk_00, ((u8 *)(&D_80082E80)),
                      &position_offset, 0);
        position.x += position_offset.x;
        state->x = position.x;
        position.y += position_offset.y;
        state->y = position.y;
        position.z += position_offset.z;
        state->z = position.z;
        state->state++;
    }
    case 1:
    {
        s32 step_offset;

        current_coord = state->cur_x;
        distance = state->x - current_coord;
        if (distance < 0) {
            distance += 7;
        }
        step_offset = (distance >> 3) * (state->step + 1);
        target->x = (u16)target->x +
            (current_coord + step_offset - target->x) / state->timer;
    }
    {
        s32 step_offset;

        current_coord = state->cur_y;
        distance = state->y - current_coord;
        if (distance < 0) {
            distance += 7;
        }
        step_offset = (distance >> 3) * (state->step + 1);
        target->y = (u16)target->y +
            (current_coord + step_offset - target->y) / state->timer;
    }
    {
        s32 step_offset;

        current_coord = state->cur_z;
        distance = state->z - current_coord;
        if (distance < 0) {
            distance += 7;
        }
        step_offset = (distance >> 3) * (state->step + 1);
        target->z = (u16)target->z +
            (current_coord + step_offset - target->z) / state->timer;
    }

    smoothed_coord = (u16)state->cur_x + ((target->x - state->cur_x) >> 2);
    state->cur_x = smoothed_coord;
    target->cur_x = smoothed_coord;
    smoothed_coord = (u16)state->cur_y + ((target->y - state->cur_y) >> 2);
    state->cur_y = smoothed_coord;
    target->cur_y = smoothed_coord;
    smoothed_coord = (u16)state->cur_z + ((target->z - state->cur_z) >> 2);
    state->cur_z = smoothed_coord;
    target->cur_z = smoothed_coord;

    phase_value = state->timer - 1;
    state->timer = phase_value;
    if ((s16)phase_value > 0) {
        return;
    }
    func_800B8D64(state->x, state->y, state->z);
    phase_value = state->state;
    const_reg = 5;
    state->timer = const_reg;
    state->state = phase_value + 1;
    return;

    case 2:
    color->unk_0C -= color->unk_0C / state->timer;
    phase_value = state->timer - 1;
    state->timer = phase_value;
    if ((s16)phase_value > 0) {
        return;
    }
    if (state->step == 0) {
        color->unk_0C = 0;
        const_reg = 4;
        state->phase = const_reg;
        phase_value = state->state;
        state->state = phase_value + 1;
        return;
    }
    *(u16 *)((u8 *)state - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    return;

    case 3:
    {
        s32 direction_offset;
        TileObject *table;

        table = &D_80082E80;
        func_8003DE58(((void *)table->unk_008), table, &position, 0);
        phase_value = state->phase - 1;
        state->phase = phase_value;
        if ((s16)phase_value > 0) {
            return;
        }
        direction_offset = ((((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_2A.u16_value >> 8) & 0xE);
        func_80025334(
            (s16)(((table->tileX +
                    (((S_func_819615E4_5 *)((u8 *)((s8 *)dirStepX) + direction_offset))->unk_00 * 4)) << 6) + 0x20),
            (s16)(((table->tileY +
                    (((S_func_819615E4_6 *)((u8 *)((s8 *)dirStepY) + direction_offset))->unk_00 * 4)) << 6) + 0x20),
            ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_88.s16_value);
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    }
    return;
}
