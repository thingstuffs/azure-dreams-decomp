#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern void func_8001ACE8(s32 arg0);
extern void *func_80019DFC(void *arg0, void *arg1, s32 arg2, s32 arg3);

extern u8 D_8001BE24[];
extern u8 D_8001C354[];
extern u8 D_8001DCD4[];
extern u8 D_8001E16A[];
extern u8 D_8001E42A[];

void *func_80018420(s32 arg0, s32 arg1, s32 arg2) {
    void *result;

    if (arg2 == 0x1E) {
        if (func_8001ADE0(0x145E) != 0) {
            if (func_8001ADE0(0x145F) != 0) {
                result = D_8001E42A;
            } else {
                result = D_8001E16A;
            }
        } else {
            result = D_8001DCD4;
            func_8001ACE8(0x145E);
        }
    } else {
        result = func_80019DFC(D_8001BE24, D_8001C354, arg0, arg2);
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
    return result;
}
