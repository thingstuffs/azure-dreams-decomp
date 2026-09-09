#include "common.h"

extern void func_800BBDEC(void *arg0, void *arg1, void *arg2, s16 arg3);

s32 func_800BC054(void *arg0, void *arg1, void *arg2) {
    void *base = arg0;
    void *node;

    for (;;) {
        func_800BBDEC(base, arg1, arg2, *(s16 *)((s8 *)arg2 + 6));
        node = *(void **)((s8 *)base - 8);
        if (node == 0) {
            return 0;
        }
        base = (void *)((s8 *)node + 32);
        arg1 = (void *)((s32 *)node)[2];
        arg2 = (void *)((s32 *)node)[3];
    }
}
