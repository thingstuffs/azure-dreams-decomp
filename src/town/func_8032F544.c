#include "common.h"

extern s32 func_800194E4(s32 arg0, s32 arg1);
extern s32 func_8001ADE0(s32 arg0);

void func_80019D44(s32 arg0, void *arg1, s32 arg2) {
    s32 idx1;
    s16 idx2;
    s32 base2;

    idx1 = func_800194E4(arg0, arg2);
    idx2 = *(s16 *)(arg0 + (idx1 * 8) + 2);
    base2 = *(s32 *)((u8 *)arg1 + 0x14);
    func_8001ADE0(*(s16 *)(base2 + (idx2 * 8) + 2));
}
