#include "common.h"
extern int abs(int);

typedef struct TownObj {
    s32 unk0;
    s32 unk4;
    s32 value8;
    s32 valueC;
    s32 value10;
    s32 value14;
} TownObj;

typedef struct TownVec {
    s16 x;
    s16 y;
    s16 divisor;
} TownVec;

extern s8 D_800CFCE9;
void func_800954F4(TownObj *arg0);

/* Computes and clamps a vector-based adjustment, then updates the town object. */
void func_80095A94(TownObj *obj, s32 base_value, TownVec **vec_ptr)
{
    TownVec *vec;
    s32 x;
    s32 y;
    s32 initial_base_value;
    s32 abs_x;
    s32 abs_y;
    s32 adjustment;
    s32 clamp_value;

    D_800CFCE9 = 1;
    initial_base_value = base_value << 16;
    obj->value8 = initial_base_value;
    vec = *vec_ptr;
    x = vec->x;
    if (x == 0 && vec->y == 0) {
        goto zero_value;
    }
    base_value = vec->divisor;
    if (base_value != 0) {
        goto calculate;
    }

zero_value:
    obj->value14 = 0;
    goto finish;

calculate:
    y = vec->y;
    abs_x = x;
    abs_x = abs(abs_x);
    abs_y = y;
    abs_y = abs(abs_y);
    if (abs_y < abs_x) {
        adjustment = (((-obj->valueC) << 8) / base_value) * x;
    } else {
        adjustment = (((-obj->value10) << 8) / base_value) * y;
    }
    if (adjustment < 0) {
        adjustment += 0xFF;
    }
    do {
        adjustment >>= 8;
    } while (0);
    obj->value14 = adjustment;
    clamp_value = *(volatile s32 *)&obj->value14;
    if (clamp_value > 0xCC000) {
        obj->value14 = 0xCC000;
    } else if (clamp_value < -0xCC000) {
        obj->value14 = -0xCC000;
    }
finish:
    func_800954F4(obj);
}
