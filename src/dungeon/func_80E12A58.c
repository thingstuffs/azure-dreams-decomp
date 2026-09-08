#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_80176290(void) __attribute__((noreturn));

#ifndef NON_MATCHING
register s32 func_80E12A58_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

s32 func_80E12A58(void *arg0) {
#ifdef NON_MATCHING
    if ((func_80042900(arg0, 0x19) << 0x10) == 0) {
#else
    func_80E12A58_v0 = func_80042900(arg0, 0x19) << 0x10;
    if (func_80E12A58_v0 == 0) {
        func_80E12A58_v0 = 0;
#endif
        func_80176290();
    }
    func_80042B68(arg0, 0x19);
    return 1;
}
