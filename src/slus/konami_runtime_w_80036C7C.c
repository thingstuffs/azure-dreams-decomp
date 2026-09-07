#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    u8 padC[0xC];
    u8 x_offset;
    u8 pad19;
    u8 y_offset;
} FuncInput;

typedef struct {
    u32 value0;
    u32 value4;
    u32 value8;
} FuncOutput;

extern u16 GetTPage(s32 tp, s32 abr, s32 x, s32 y);

void func_80036C7C(FuncInput *arg0, u32 *arg1, FuncOutput *arg2) {
    arg2->value0 = arg1[0];
    arg2->value4 = arg1[1];
    arg2->value8 = arg1[2];
    ((u16 *)&arg2->value4)[0] = GetTPage(0, 1, arg0->x, arg0->y);
    ((u8 *)&arg2->value8)[0] += arg0->x_offset + (arg0->x % 64) * 4;
    ((u8 *)&arg2->value8)[1] += (arg0->y % 256) + arg0->y_offset;
}
