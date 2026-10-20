#include "common.h"

s32 func_80018B00();                                /* extern */

/* Returns whether func_80018B00 reports zero. */
s32 is_status_zero(void) {
    return func_80018B00() == 0;
}
