#include "common.h"

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
    register s32 x ASM_REG("$7");
    s32 y;
    s32 divisor;
    s32 abs_x;
    register s32 abs_y ASM_REG("$2");
    s32 adjustment;
    s32 clamp_value;

    D_800CFCE9 = 1;
    base_value <<= 16;
    obj->value8 = base_value;
    vec = *vec_ptr;
    x = vec->x;
    if (x == 0 && vec->y == 0) {
        goto zero_value;
    }
    divisor = vec->divisor;
    if (divisor != 0) {
        goto calculate;
    }

zero_value:
    obj->value14 = 0;
    goto finish;

calculate:
    y = vec->y;
    abs_x = (x < 0) ? -x : x;
    abs_y = y;
    if (y < 0) {
        abs_y = -abs_y;
    }
    if (abs_y < abs_x) {
        adjustment = (((-obj->valueC) << 8) / divisor) * x;
    } else {
        adjustment = (((-obj->value10) << 8) / divisor) * y;
    }
    if (adjustment < 0) {
        adjustment += 0xFF;
    }
    adjustment >>= 8;
    obj->value14 = adjustment;
    ASM_KEEP(adjustment);
    clamp_value = *(volatile s32 *)&obj->value14;
    if (clamp_value > 0xCC000) {
        obj->value14 = 0xCC000;
    } else if (clamp_value < -0xCC000) {
        obj->value14 = -0xCC000;
    }
finish:
    func_800954F4(obj);
}
