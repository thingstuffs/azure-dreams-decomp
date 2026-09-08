#include "common.h"

s32 func_80017200();
s32 func_800173CC();
s32 func_80017FEC();

s32 func_80016154(s32 arg0, s32 arg1) {
    s32 result;
    s32 first;
    register s32 call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    first = func_80017FEC();
    call_arg = arg0;
    if (first < 2) {
        goto check_second;
    }
    return func_80017200(call_arg, arg1);

check_second:
    result = 0;
    if (func_80017FEC(call_arg) > 0) {
        result = func_800173CC(arg0, arg1) != 0;
    }
    return result;
}

/* MECHANISM: The two arguments remain held in s1/s2 across calls, while result
   occupies s0 and preserves retail's 0x20 frame/save order.  A short-lived a0
   call_arg moves the common setup and zero-init into their retail delay slots. */
