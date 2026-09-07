#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern void *func_8003FC64();
extern void func_8004491C();
extern s16 func_800644B8();
extern s16 func_80064584();
extern s32 rand();
extern s32 D_80025460[];
extern s32 D_800258D8[];

void func_8196012C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s32 random;
    s32 random_arg;
    s16 arg4_copy;
    void *position;
    void *primitive;
    void *render;
    void *object;

    arg4_copy = arg4;
    object = func_8003FC64(0x202);
    if (object != NULL) {
        FIELD(object, s32 *, 0x10) = D_80025460;
        func_8004491C(object, D_800258D8);
        position = FIELD(object, void *, 8);
        FIELD(position, s16, 2) = arg0;
        FIELD(position, s16, 6) = arg1;
        FIELD(position, s16, 0xA) = arg2;
        FIELD(position, s16, 0xE) = (rand() & 0xF) - 8;
        FIELD(position, s16, 0x12) = (rand() & 0xF) - 8;
        FIELD(position, s16, 0x16) = -0x10 - (rand() & 0xF);
        render = FIELD(object, void *, 0xC);
        FIELD(render, s16, 0x1E) = 0x400;
        FIELD(render, s16, 0x1C) = 0x400;
        random = rand();
        FIELD(render, s16, 0x20) = func_80064584(random);
        FIELD(render, s16, 0x22) = func_800644B8(random);
        FIELD(render, s16, 0x10) = 0x20;
        primitive = (s8 *)object + 0x20;
        FIELD(render, s16, 0x14) = 0xC;
        FIELD(render, s32, 0xC) = 0x808080;
        random_arg = 0xF8F82CC0;
        FIELD(object, s32, 0x20) = random_arg;
        FIELD(primitive, s16, 4) = 0x13D;
        FIELD(primitive, s8, 8) = (s8)(arg3 * 0x10);
        FIELD(primitive, s8, 9) = (s8)(((s32)(arg4 << 0x10) >> 0xC) - 0x80);
        FIELD(primitive, s8, 0xA) = arg3 == 7 ? 0xF : 0x10;
        FIELD(primitive, s8, 0xB) = arg4_copy == 7 ? 0xF : 0x10;
        FIELD(primitive, s16, 0x4C) = (rand(random_arg) & 0x1F) + 0x20;
        FIELD(render, void *, 8) = primitive;
    }
}
