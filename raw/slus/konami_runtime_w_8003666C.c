#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type)((u8 *)(base) + (offset)))

extern u8 D_80082040[0x10];
extern u8 D_80082538[0x10];

extern void func_800366F4(void);
extern void func_8003719C(s32, void *, s32 *, s16, s32, s32);

void func_8003666C(s32 *arg0) {
    s32 inner;
    u8 marker;
    s32 position;
    s16 result;

    inner = (s32) FIELD(arg0, void **, 0x74);
    marker = FIELD((void *) inner, u8 *, 0x27);
    position = FIELD((void *) inner, s16 *, 0x22);
    inner = FIELD((void *) inner, u8 *, 0x26);
    inner = ((inner + 1) >> 1) - 1;
    position -= inner;
    result = (s16) (position * 2);
    FIELD(arg0, u8 *, 0x4D) = marker;
    func_8003719C(
        (s32) D_80082538,
        D_80082040,
        arg0,
        1,
        result,
        FIELD(FIELD(arg0, void **, 0x74), s32 *, 0x80));
    FIELD(arg0, void (**)(void), 0x68) = func_800366F4;
}
