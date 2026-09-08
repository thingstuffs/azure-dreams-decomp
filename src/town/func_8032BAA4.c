#include "common.h"

typedef s32 M2C_UNK;

extern void func_800162C0(void) __attribute__((noreturn));
extern M2C_UNK D_8001DCD4;
extern M2C_UNK D_8001DF1B;

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

M2C_UNK *func_800162A4(s32 arg0, s32 arg1, s32 arg2) {
#ifndef NON_MATCHING
    dispatch_result = 1;
    if (arg2 != dispatch_result) {
        dispatch_result = 0x80020000;
        dispatch_result -= 0x232C;
#else
    if (arg2 != 1) {
        (void)D_8001DCD4;
#endif
        func_800162C0();
    }
#ifndef NON_MATCHING
    dispatch_result = 0x80020000;
    dispatch_result -= 0x20E5;
    return (M2C_UNK *)dispatch_result;
#else
    return &D_8001DF1B;
#endif
}
