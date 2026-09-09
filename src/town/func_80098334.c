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

void func_80095A94(TownObj *arg0, s32 arg1, TownVec **arg2)
{
    TownVec *vec;
    register s32 x ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 y;
    s32 divisor;
    s32 absX;
    register s32 absY ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value;
    s32 clampValue;

    D_800CFCE9 = 1;
    arg1 <<= 16;
    arg0->value8 = arg1;
    vec = *arg2;
    x = vec->x;
    if (x == 0 && vec->y == 0) {
        goto zero_value;
    }
    divisor = vec->divisor;
    if (divisor != 0) {
        goto calculate;
    }

zero_value:
    arg0->value14 = 0;
    goto finish;

calculate:
    y = vec->y;
    absX = (x < 0) ? -x : x;
    absY = y;
    if (y < 0) {
        absY = -absY;
    }
    if (absY < absX) {
        value = (((-arg0->valueC) << 8) / divisor) * x;
    } else {
        value = (((-arg0->value10) << 8) / divisor) * y;
    }
    if (value < 0) {
        value += 0xFF;
    }
    value >>= 8;
    arg0->value14 = value;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    clampValue = *(volatile s32 *)&arg0->value14;
    if (clampValue > 0xCC000) {
        arg0->value14 = 0xCC000;
    } else if (clampValue < -0xCC000) {
        arg0->value14 = -0xCC000;
    }
finish:
    func_800954F4(arg0);
}

/* MECHANISM: True-space jumps are local joins, yielding the retail 0x18 ra-only frame.
   Signed halfword roles use pinned x/$a3 and absY,value/$v0 lifetimes across both arms.
   A post-store value keep plus volatile reread orders retail's sw/lui/lw clamp sequence. */
