#include "common.h"

extern void func_80098748(s16 arg0);
extern void func_80099754(void *arg0);
extern void func_80098928(void *arg0, void *arg1, s32 arg2);

void func_80098690(u8 *arg0, u8 *arg1, s32 arg2) {
    s16 count;
    s16 count2;

    count = (*(u16 *)(arg0 + 0xA) -= 1);
    if (count > 0) {
        *(s32 *)(arg1 + 0) += (((s32) *(s16 *)(arg0 + 0x30) << 16) - *(s32 *)(arg1 + 0)) / count;
        *(s32 *)(arg1 + 4) += (((s32) *(s16 *)(arg0 + 0x32) << 16) - *(s32 *)(arg1 + 4)) / (count2 = *(s16 *)(arg0 + 0xA));
        func_80098748(count2);
        return;
    }
    *(u16 *)(arg1 + 2) = *(u16 *)(arg0 + 0x30);
    *(u16 *)(arg1 + 6) = *(u16 *)(arg0 + 0x32);
    func_80099754(arg1);
    func_80098928(arg0, arg1, arg2);
}
