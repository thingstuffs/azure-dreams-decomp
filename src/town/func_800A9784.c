#include "common.h"

extern void func_800A6F48(void *arg0, void *arg1);

void func_800A6EE4(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    u16 t1;
    u16 t0;

    t1 = *(u16 *) ((u8 *) arg0 + 0x90) + 4;
    *(u16 *) ((u8 *) arg0 + 0x90) = t1;
    t0 = *(u16 *) ((u8 *) arg3 + 0x16) + t1;
    *(u16 *) ((u8 *) arg3 + 0x16) = t0;
    if (t0 >= 0x400) {
        t0 = 0x400;
        *(u16 *) ((u8 *) arg3 + 0x16) = t0;
    }
    if (*(u16 *) ((u8 *) arg3 + 0x16) == 0x400) {
        func_800A6F48(arg0, arg0);
    }
}
