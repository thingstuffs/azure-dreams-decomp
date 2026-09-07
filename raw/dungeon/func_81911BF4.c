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
extern void func_8002581C(void) __attribute__((noreturn));
extern void func_80025824(void) __attribute__((noreturn));
extern s32 D_800814A0;

void func_800253F4(Obj81911BF4 *arg0, s32 *arg1)
{
    Obj81911BF4 *obj = arg0;
    s32 *base = arg1;
    s32 phase;
    volatile Obj81911BF4 *out;
    s32 i;
    register u8 fade45 ASM_REG("$3");
    u16 value;
    u16 step45;
    u16 scale45;
    u16 duration_value;
    s16 sum;
    s32 signed_sum;
    register s32 modulo45 ASM_REG("$9");
    u8 byte_value;
    s32 state;

    ASM_KEEP(base);
    obj->inner->field14++;
    obj->timer++;

    i = 0;
    out = obj;
    phase = 0;
    do {
        out->x[0] = base[0] + (((func_800644B8(phase + obj->angle) >> 4) * obj->scale) << 8);
        out->y[0] = base[1] + (((func_80064584(phase + obj->angle) >> 4) * obj->scale) << 8);
        i++;
        phase += 0x333;
        out = (volatile Obj81911BF4 *)((u8 *)out + 4);
    } while (i < 5);

    state = obj->state;
    if ((u32)state >= 7U) {
        return;
    }

    switch (state) {
    case 0:
        func_8002429C(obj, base, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        base[2] = obj->field14 << 16;
        func_8002581C();
        return;

    case 1:
        func_800246C0(obj, base, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        {
            register u16 duration_c1 ASM_REG("$3") = 4;
            ASM_KEEP(duration_c1);
            (void)*(volatile u16 *)&obj->state;
            obj->timer = 0;
            obj->duration = duration_c1;
            func_80025824();
        }
        return;

    case 2:
        func_800246C0(obj, base, 0, 0);
        func_80024ACC(obj, base, obj->timer, obj->duration);
        if (obj->timer < obj->duration) {
            return;
        }
        {
            register u16 value_c2 ASM_REG("$2") = 3;
            register u16 duration_c2 ASM_REG("$3");
            ASM_KEEP(value_c2);
            obj->field12 = value_c2;
            ASM_KEEP(value_c2);
            value_c2 = *(volatile u16 *)&obj->state;
            ASM_KEEP(value_c2);
            duration_c2 = 0x10;
            ASM_KEEP(duration_c2);
            obj->timer = 0;
            obj->duration = duration_c2;
            func_80025824();
        }
        return;

    case 3:
        obj->angle_step += 0x10;
        obj->angle += obj->angle_step;
        signed_sum = obj->angle;
        obj->field10 += 0x10;
        obj->angle = signed_sum % 0x1000;
        func_800246C0(obj, base, 0, 0);
        func_80024ACC(obj, base, 0, 0);
        if (obj->timer < obj->duration) {
            return;
        }
        goto advance;

    case 4:
        step45 = obj->angle_step;
        sum = (u16)obj->angle;
        ASM_SCHED_BARRIER();
        fade45 = obj->field42;
        ASM_SCHED_BARRIER();
        step45 += 0x10;
        sum += step45;
        signed_sum = (s16)sum;
        ASM_KEEP(signed_sum);
        modulo45 = signed_sum;
        ASM_USE(modulo45);
        scale45 = (u16)obj->scale;
        ASM_SCHED_BARRIER();
        fade45 += 0x0C;
        obj->field42 = fade45;
        obj->field41 = fade45;
        obj->angle_step = step45;
        obj->angle = sum;
        obj->scale = scale45 - 4;
        obj->angle = signed_sum % 0x1000;
        func_800246C0(obj, base, 0, 0);
        func_80024ACC(obj, base, 0, 0);
        if (obj->timer < obj->duration) {
            return;
        }
        func_8002539C(obj);
        {
            register u16 state_c4 ASM_REG("$2");
            register u16 duration_c4 ASM_REG("$3");
            state_c4 = *(volatile u16 *)&obj->state;
            ASM_KEEP(state_c4);
            duration_c4 = 0x20;
            ASM_KEEP(duration_c4);
            obj->timer = 0;
            obj->duration = duration_c4;
            func_80025824();
        }
        return;

    case 5:
        step45 = obj->angle_step;
        sum = (u16)obj->angle;
        ASM_SCHED_BARRIER();
        fade45 = obj->field42;
        ASM_SCHED_BARRIER();
        step45 += 0x10;
        sum += step45;
        signed_sum = (s16)sum;
        ASM_KEEP(signed_sum);
        modulo45 = signed_sum;
        ASM_USE(modulo45);
        scale45 = (u16)obj->scale;
        ASM_SCHED_BARRIER();
        fade45 -= 6;
        obj->field42 = fade45;
        obj->field41 = fade45;
        obj->field40 = fade45;
        obj->angle_step = step45;
        obj->angle = sum;
        obj->scale = scale45 + 0x0C;
        obj->angle = signed_sum % 0x1000;
        func_800246C0(obj, base, 0, 0);
        obj->scale = (u16)obj->scale * 2;

        i = 0;
        out = obj;
        phase = 0;
        do {
            out->x[0] = base[0] + (((func_800644B8(phase + obj->angle) >> 4) * obj->scale) << 9);
            out->y[0] = base[1] + (((func_80064584(phase + obj->angle) >> 4) * obj->scale) << 9);
            i++;
            phase += 0x333;
            out = (volatile Obj81911BF4 *)((u8 *)out + 4);
        } while (i < 5);

        func_80024ACC(obj, base, 0, 0);
        obj->scale = ((s32)(u16)obj->scale << 16) >> 17;
        if (obj->timer < obj->duration) {
            return;
        }

advance:
        obj->timer = 0;
        obj->state++;
        return;

    case 6:
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
