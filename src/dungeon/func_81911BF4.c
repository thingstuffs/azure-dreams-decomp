#include "common.h"

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
extern s32 D_800814A0;

/* Update the five orbiting points and advance the effect animation. */
void func_800253F4(Obj81911BF4 *effect, s32 *position)
{
    Obj81911BF4 *obj = effect;
    s32 *origin = position;
    s32 phase_offset;
    volatile Obj81911BF4 *point;
    s32 point_index;
    register u8 brightness ASM_REG("$3");
    register u16 state_value;
    u16 angle_step;
    u16 scale;
    s16 angle_sum;
    s32 signed_angle;
    register s32 angle_dividend ASM_REG("$9");
    s32 state;

    ASM_KEEP(origin);
    obj->inner->field14++;
    obj->timer++;

    point_index = 0;
    point = obj;
    phase_offset = 0;
    do {
        point->x[0] = origin[0] + (((func_800644B8(phase_offset + obj->angle) >> 4) * obj->scale) << 8);
        point->y[0] = origin[1] + (((func_80064584(phase_offset + obj->angle) >> 4) * obj->scale) << 8);
        point_index++;
        phase_offset += 0x333;
        point = (volatile Obj81911BF4 *)((u8 *)point + 4);
    } while (point_index < 5);

    state = obj->state;
    if ((u32)state >= 7U) {
        return;
    }

    switch (state) {
    case 0:
        func_8002429C(obj, origin, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        origin[2] = obj->field14 << 16;
        goto advance;

    case 1:
        func_800246C0(obj, origin, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        {
            register u16 next_duration ASM_REG("$3") = 4;
            ASM_KEEP(next_duration);
            state_value = *(volatile u16 *)&obj->state;
            obj->timer = 0;
            obj->duration = next_duration;
            goto increment;
        }
        return;

    case 2:
        func_800246C0(obj, origin, 0, 0);
        func_80024ACC(obj, origin, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        {
            register u16 next_duration ASM_REG("$3");
            state_value = 3;
            obj->field12 = state_value;
            state_value = *(volatile u16 *)&obj->state;
            next_duration = 0x10;
            obj->timer = 0;
            ASM_SCHED_BARRIER();
            obj->duration = next_duration;
            goto increment;
        }
        return;

    case 3:
        obj->angle_step += 0x10;
        obj->angle += obj->angle_step;
        signed_angle = obj->angle;
        obj->field10 += 0x10;
        obj->angle = signed_angle % 0x1000;
        func_800246C0(obj, origin, 0, 0);
        func_80024ACC(obj, origin, 0, 0);
        if (obj->timer < obj->duration) {
            return;
        }
        goto advance;

    case 4:
        angle_step = obj->angle_step;
        angle_sum = (u16)obj->angle;
        brightness = obj->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        ASM_USE(angle_dividend);
        scale = (u16)obj->scale;
        brightness += 0x0C;
        obj->field42 = brightness;
        obj->field41 = brightness;
        obj->angle_step = angle_step;
        obj->angle = angle_sum;
        obj->scale = scale - 4;
        obj->angle = signed_angle % 0x1000;
        func_800246C0(obj, origin, 0, 0);
        func_80024ACC(obj, origin, 0, 0);
        if (obj->timer < obj->duration) {
            return;
        }
        func_8002539C(obj);
        {
            register u16 next_duration ASM_REG("$3");
            state_value = *(volatile u16 *)&obj->state;
            next_duration = 0x20;
            obj->timer = 0;
            ASM_SCHED_BARRIER();
            obj->duration = next_duration;
            goto increment;
        }
        return;

    case 5:
        angle_step = obj->angle_step;
        angle_sum = (u16)obj->angle;
        brightness = obj->field42;
        angle_step += 0x10;
        angle_sum += angle_step;
        signed_angle = (s16)angle_sum;
        angle_dividend = signed_angle;
        ASM_USE(angle_dividend);
        scale = (u16)obj->scale;
        brightness -= 6;
        obj->field42 = brightness;
        obj->field41 = brightness;
        obj->field40 = brightness;
        obj->angle_step = angle_step;
        obj->angle = angle_sum;
        obj->scale = scale + 0x0C;
        obj->angle = signed_angle % 0x1000;
        func_800246C0(obj, origin, 0, 0);
        obj->scale = (u16)obj->scale * 2;

        point_index = 0;
        point = obj;
        phase_offset = 0;
        do {
            point->x[0] = origin[0] + (((func_800644B8(phase_offset + obj->angle) >> 4) * obj->scale) << 9);
            point->y[0] = origin[1] + (((func_80064584(phase_offset + obj->angle) >> 4) * obj->scale) << 9);
            point_index++;
            phase_offset += 0x333;
            point = (volatile Obj81911BF4 *)((u8 *)point + 4);
        } while (point_index < 5);

        func_80024ACC(obj, origin, 0, 0);
        obj->scale = ((s32)(u16)obj->scale << 16) >> 17;
        if (obj->timer < obj->duration) {
            return;
        }

advance:
        state_value = obj->state;
        obj->timer = 0;
increment:
        obj->state = state_value + 1;
        return;

    case 6:
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
