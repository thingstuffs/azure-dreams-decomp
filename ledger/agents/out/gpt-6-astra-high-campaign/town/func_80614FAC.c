#include "common.h"

extern void func_80018B58(s32);
extern void func_80018BD0(s32);
extern s32 func_80018C50(s32);

/* Reset two flags and set flag 0x67C when the prerequisite flags allow it. */
s32 func_800167AC(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    if (func_80018C50(0x679) == 0) {
        return 0;
    }
    if (func_80018C50(0x67A) != 0) {
        return 0;
    }
    func_80018B58(0x67C);
    return 1;
}
