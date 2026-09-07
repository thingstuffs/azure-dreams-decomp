#include "common.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

s32 func_800163E8(void) {
    if (func_80018C50(0xFC0) != 0) {
        func_80018B58(0xFB5);
        return 1;
    }

    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    return 0;
}
