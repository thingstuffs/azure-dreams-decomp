#include "common.h"

extern s32 func_8001ACE8();
extern s32 func_8001AD60();

s32 func_80019988(void *arg0, s32 arg1) {
    func_8001AD60(*(s16 *)((s8 *)arg0 + 0x18));
    func_8001ACE8(*(s16 *)((arg1 * 0x10) + *(s32 *)((s8 *)arg0 + 0x10) + 0xC));
    return 1;
}
