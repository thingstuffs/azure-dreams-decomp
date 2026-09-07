#include "common.h"

extern void func_800453E0(void *arg0, s32 arg1, void *arg2, s32 arg3);

s32 func_80175D74(u8 *arg0, s32 arg1, u8 *arg2) {
    *(s32 *)0x1F80013C = 0;
    for (;;) {
        func_800453E0(arg0, arg1, arg2, -0x10);
        arg2 = *(u8 **)(arg0 - 8);
        if (arg2 == 0) {
            return 0;
        }
        arg0 = arg2 + 0x20;
        arg1 = *(s32 *)(arg2 + 8);
        arg2 = *(u8 **)(arg2 + 0xC);
    }
}

/* MECHANISM: The true-space j to 0x80175D90 is a local loop backedge, not an external tail call.
   Natural loop liveness holds arg0 in s0, yielding the 24-byte frame and exact save order.
   Testing arg2 before its source-level advance lets gcc place that advance in the branch delay slot. */
