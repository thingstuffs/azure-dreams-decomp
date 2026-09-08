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

/* Copies texture data and adjusts its texture page and UV coordinates. */
void func_80036C7C(FuncInput *texture_pos, u32 *src, FuncOutput *dst) {
    dst->value0 = src[0];
    dst->value4 = src[1];
    dst->value8 = src[2];
    ((u16 *)&dst->value4)[0] = GetTPage(0, 1, texture_pos->x, texture_pos->y);
    ((u8 *)&dst->value8)[0] += texture_pos->x_offset + (texture_pos->x % 64) * 4;
    ((u8 *)&dst->value8)[1] += (texture_pos->y % 256) + texture_pos->y_offset;
}
