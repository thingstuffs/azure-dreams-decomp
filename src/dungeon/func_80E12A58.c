#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_80176290(void) __attribute__((noreturn));

/* Checks object code 0x19, exits on failure, and applies it on success. */
s32 func_80E12A58(void *object) {
#ifdef NON_MATCHING
    if ((func_80042900(object, 0x19) << 0x10) == 0) {
        func_80176290();
    }
    func_80042B68(object, 0x19);
    return 1;
#else
    switch (func_80042900(object, 0x19) << 0x10) {
    default:
        func_80042B68(object, 0x19);
        return 1;
    case 0:
        return 0;
    }
#endif
}
