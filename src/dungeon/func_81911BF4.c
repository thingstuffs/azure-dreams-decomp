#include "common.h"
#include "shared/object_flags.h"

typedef struct Inner81911BF4 {
    u8 pad00[0x14];
    u16 field14;
} Inner81911BF4;

typedef struct Obj81911BF4 {
    Inner81911BF4 *inner;
    s16 state;
    s16 timer;
    s16 duration;
    s16 angle;
    u16 angle_step;
    s16 scale;
    u16 field10;
    s16 field12;
    s16 field14;
    s32 x[5];
    s32 y[5];
    u8 field40;
    u8 field41;
    u8 field42;
} Obj81911BF4;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8002429C(Obj81911BF4 *, s32 *, s32, s32);
extern void func_800246C0(Obj81911BF4 *, s32 *, s32, s32);
extern void func_80024ACC(Obj81911BF4 *, s32 *, s32, s32);
extern void func_8002539C(Obj81911BF4 *);

/* Update the five orbiting points and advance the effect animation. */
void func_800253F4(Obj81911BF4 *effect, s32 *position)
{
    s32 phase_offset;
    volatile Obj81911BF4 *point;
    s32 point_index;
    s32 brightness;
    s32 fade;
    u16 angle_step;
    s16 angle_sum;
    s32 signed_angle;
    s32 angle_dividend;
    s32 state;

    effect->inner->field14++;
    effect->timer++;

    point_index = 0;
    point = effect;
    phase_offset = 0;
loop_0:
    {
        point->x[0] = position[0] + (((func_800644B8(phase_offset + effect->angle) >> 4) * effect->scale) << 8);
        point->y[0] = position[1] + (((func_80064584(phase_offset + effect->angle) >> 4) * effect->scale) << 8);
        point_index++;
        phase_offset += 0x333;
        point = (Obj81911BF4 *)((u8 *)point + 4);
    }
    if (point_index < 5)
        goto loop_0;

    state = effect->state;
    if ((u32)state >= 7U) {
        return;
    }

    switch (state) {
    case 0:
        func_8002429C(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        position[2] = effect->field14 << 16;
        effect->timer = 0;
        effect->state++;
        return;

    case 1:
        func_800246C0(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->duration = 4;
        effect->state++;
        return;

    case 2:
        func_800246C0(effect, position, 0, 0);
        func_80024ACC(effect, position, effect->timer, effect->duration);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->field12 = 3;
        effect->timer = 0;
        effect->duration = 0x10;
        effect->state++;
        return;

    case 3:
        effect->angle_step += 0x10;
        effect->angle += effect->angle_step;
        signed_angle = effect->angle;
        effect->field10 += 0x10;
        effect->angle = signed_angle % 0x1000;
        func_800246C0(effect, position, 0, 0);
        func_80024ACC(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        effect->timer = 0;
        effect->state++;
        return;

    case 4:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        brightness = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        brightness += 0x0C;
        effect->field42 = brightness;
        effect->field41 = brightness;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale - 4;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        func_800246C0(effect, position, 0, 0);
        func_80024ACC(effect, position, 0, 0);
        if (effect->timer < effect->duration) {
            return;
        }
        func_8002539C(effect);
        effect->timer = 0;
        effect->duration = 0x20;
        effect->state++;
        return;

    case 5:
        angle_step = effect->angle_step;
        angle_sum = (u16)effect->angle;
        fade = effect->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        fade -= 6;
        effect->field42 = fade;
        effect->field41 = fade;
        effect->field40 = fade;
        effect->angle_step = angle_step;
        effect->angle = angle_sum;
        effect->scale = (u16)effect->scale + 0x0C;
        if (angle_dividend < 0) {
            angle_dividend += 0xFFF;
        }
        effect->angle = signed_angle - ((angle_dividend >> 12) << 12);
        func_800246C0(effect, position, 0, 0);
        effect->scale = (u16)effect->scale * 2;

        point_index = 0;
        point = effect;
        phase_offset = 0;
        do {
            point->x[0] = position[0] + (((func_800644B8(phase_offset + effect->angle) >> 4) * effect->scale) << 9);
            point->y[0] = position[1] + (((func_80064584(phase_offset + effect->angle) >> 4) * effect->scale) << 9);
            point_index++;
            phase_offset += 0x333;
            point = (Obj81911BF4 *)((u8 *)point + 4);
        } while (point_index < 5);

        func_80024ACC(effect, position, 0, 0);
        effect->scale = ((s32)(u16)effect->scale << 16) >> 17;
        if (effect->timer < effect->duration) {
            return;
        }

        effect->timer = 0;
        effect->state++;
        return;

    case 6:
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
}
