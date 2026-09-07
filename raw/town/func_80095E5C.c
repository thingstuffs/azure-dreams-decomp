#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_80093D48(void);

void func_800935BC(void *arg0, void *arg1) {
    s16 temp_v0;

    FIELD(arg1, s32, 0x0) = (s32) (((s32) (FIELD(arg0, s16, 0x30) << 0x10) + FIELD(arg1, s32, 0x0)) / 2);
    FIELD(arg1, s32, 0x4) = (s32) (((s32) (FIELD(arg0, s16, 0x32) << 0x10) + FIELD(arg1, s32, 0x4)) / 2);
    temp_v0 = FIELD(arg0, u16, 0xA) - 1;
    FIELD(arg0, u16, 0xA) = temp_v0;
    if (temp_v0 < 0) {
        func_80093D48();
    }
}
