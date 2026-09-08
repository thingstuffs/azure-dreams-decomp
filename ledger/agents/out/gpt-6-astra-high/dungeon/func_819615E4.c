#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

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

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u16 D_80027330[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083780[];
extern void **D_800E3D18;
extern u8 *D_800E3D7C;

extern void func_80025334(s16, s16, s16);
extern void func_8002711C(void) __attribute__((noreturn));
extern void func_800271EC(void) __attribute__((noreturn));
extern void func_8003DE58(void *, void *, Vec3s *, s16);
extern void func_800B8D64(s16, s16, s16);

/* Interpolate the target position, fade its color, and finish the transition. */
void func_819615E4(State *state, Target *target, u8 *color)
{
    Vec3s position_offset;
    Vec3s position;
    s32 distance;
    s32 current_coord;
    s16 smoothed_coord;
    u16 phase_value;
    register u32 table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    D_80027330[0]++;

    if (state->state == 1) {
        goto update;
    }
    if (state->state < 2) {
        if (state->state == 0) {
            goto init;
        }
        func_800271EC();
        return;
    }

    ASM_KEEP(color);   /* MATCH pin: retail immediate-load split depends on it */
    if (state->state == 2) {
        goto fade;
    }
    if (state->state == 3) {
        table_page = 0x80080000;
        goto phase;
    }
    func_800271EC();
    return;

init:
    {
        s32 transform_offset;
        u8 *spawn = D_80083780;

        position.x = *(u16 *)(spawn + 2);
        position.y = *(u16 *)(spawn + 6);
        position.z = *(u16 *)(D_800E3D7C + 0x88) - 0x50;
        transform_offset = ((D_80083228 + *(s16 *)(D_800E3D7C + 0x2A) + 0x100) >> 7) & 0x1C;
        func_8003DE58(*(void **)((s32)transform_offset + (s32)D_800E3D18), D_80082E80,
                      &position_offset, 0);
        position.x += position_offset.x;
        state->x = position.x;
        position.y += position_offset.y;
        state->y = position.y;
        position.z += position_offset.z;
        state->z = position.z;
        state->state++;
    }
update:
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
    ASM_KEEP(phase_value);   /* MATCH pin: retail basic-block layout depends on it */
    {
        register u16 reset_timer ASM_REG("$3") = 5;   /* MATCH pin: retail register colouring depends on it */

        state->timer = reset_timer;
    }
    func_8002711C();
    return;

fade:
    color[0xC] -= color[0xC] / state->timer;
    phase_value = state->timer - 1;
    state->timer = phase_value;
    if ((s16)phase_value > 0) {
        return;
    }
    if (state->step == 0) {
        color[0xC] = 0;
        state->phase = 4;
        state->state++;
        func_800271EC();
        return;
    }
    goto finish;

phase:
    {
        s32 direction_offset;
        u8 *table;

        table = (u8 *)(table_page + 0x2E80);
        func_8003DE58(*(void **)(table + 8), table, &position, 0);
        phase_value = state->phase - 1;
        state->phase = phase_value;
        if ((s16)phase_value > 0) {
            return;
        }
        direction_offset = ((*(u16 *)(D_800E3D7C + 0x2A) >> 8) & 0xE);
        func_80025334(
            (s16)(((table[0x24] +
                    (*(s16 *)((u8 *)&D_8006CCD8 + direction_offset) * 4)) << 6) + 0x20),
            (s16)(((table[0x25] +
                    (*(s16 *)((u8 *)&D_8006CCE8 + direction_offset) * 4)) << 6) + 0x20),
            *(s16 *)(D_800E3D7C + 0x88));
finish:
        FIELD(state, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
