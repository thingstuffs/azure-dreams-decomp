#include "common.h"

typedef s32 unk32;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern unk32 D_800D58B8;

s32 func_800C648C(void *arg0) {
    s32 value;

    value = *FIELD(arg0, s32 **, 0x7C);
    if ((value == (s32)&D_800D58B8) &&
        (FIELD(FIELD(arg0, void **, 0x80), s32, 4) == value)) {
        return 1;
    }
    return 0;
}
