#include "common.h"

s32 func_80018B00();                                /* extern */

/* Returns whether func_80018B00 reports zero. */
s32 func_8059E620(void) {
    return func_80018B00() == 0;
}
