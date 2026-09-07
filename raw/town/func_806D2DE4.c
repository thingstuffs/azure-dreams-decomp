#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80016584();
extern void func_80016CCC();
extern void func_80016D20();

s32 func_800165E4(void *arg0, s32 arg1) {
    u32 entry;
    s16 value;

    arg1 *= 0x10;
    entry = arg1 + FIELD(arg0, u32, 0x10);
    value = FIELD((void *)entry, s16, 0xC);
    if (value == 0) {
        return 0;
    }
    if (func_80016584() == 0) {
        return 0;
    }
    func_80016CCC(value);
    func_80016D20(FIELD(arg0, s16, 0x18));
    ASM_USE(arg0);
    return 1;
}
