#include "common.h"

extern s32 func_8009EB9C(s32 arg0, void *arg1, s32 arg2, s32 arg3, void *arg4);
extern void func_8009BFD8(s32 arg0, void *arg1, s32 arg2, s32 arg3);

// Clear the subject flag and run the fallback actor handler if the check fails.
void func_8009EAB0(s32 actor, void *subject, s32 motion, s32 context) {
    s32 scratch[6];

    *((s8 *)subject + 0x15) = 0;
    if (func_8009EB9C(actor, subject, motion, context, scratch) == 0) {
        func_8009BFD8(actor, subject, motion, context);
    }
}
