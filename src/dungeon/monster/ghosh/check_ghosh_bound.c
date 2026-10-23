#include "common.h"

/* The local callee consumes a signed bound in a0 and returns its sample in v0.
 * See docs/evidence/r121_hardholds.md for its complete body and placement. */
extern s32 func_8016ADB8(s32 bound);

/* Calls func_8016ADB8 with bound and returns its result. */
s32 check_ghosh_bound(s32 bound) {
    return func_8016ADB8(bound);
}
