#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800199DC(void);
extern s32 func_8001ACE8(s16 value);
extern s32 func_8001AD60(s16 value);

s32 func_80019B54(void *arg0, s32 arg1) {
    if (func_800199DC() != 0) {
        func_8001ACE8(FIELD((arg1 * 0x10) + FIELD(arg0, s32, 0x10), s16, 0xC));
        func_8001AD60(FIELD(arg0, s16, 0x18));
        ASM_USE(arg1);
        return 1;
    }
    return 0;
}
