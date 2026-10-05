#include "common.h"

extern s32 func_8009EB9C(s32 context, void *subject, s32 motion, s32 extra, void *scratch);
extern void func_8009BFD8(s32 object, void *context, s32 position, s32 output);

// Clear the subject flag and run the fallback actor handler if the check fails.
void func_8009EAB0(s32 actor, void *subject, s32 motion, s32 context) {
    s32 scratch[6];

    *((s8 *)subject + 0x15) = 0;
    if (func_8009EB9C(actor, subject, motion, context, scratch) == 0) {
        func_8009BFD8(actor, subject, motion, context);
    }
}
