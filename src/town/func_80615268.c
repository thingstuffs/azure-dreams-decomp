#include "common.h"

extern s32 func_80018B58();
extern s32 func_80018BD0();
extern s32 func_80018C50();

/* Reset two flags, set flag 0xFE4, and set flag 0x680 if flag 0x11FD is active. */
s32 func_80016A68(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    func_80018B58(0xFE4);
    if (func_80018C50(0x11FD) != 0) {
        func_80018B58(0x680);
        return 1;
    }
    return 0;
}
