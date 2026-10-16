#include "common.h"

/* The local callee consumes a signed bound in a0 and returns its sample in v0.
 * See docs/evidence/r121_hardholds.md for its complete body and placement. */
extern s32 func_8016ADB8(s32 bound);

s32 func_8016DEE8(s32 bound) {
    return func_8016ADB8(bound);
}
