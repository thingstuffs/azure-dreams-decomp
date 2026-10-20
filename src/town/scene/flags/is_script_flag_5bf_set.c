#include "common.h"

s32 func_80018B5C();                         /* extern */

/* Returns whether func_80018B5C reports a nonzero result for 0x5BF. */
s32 is_script_flag_5bf_set(void) {
    return func_80018B5C(0x5BF) != 0;
}
