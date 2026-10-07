#include "common.h"

#include "common.h"

s32 func_80034FD0(void *record);                                /* extern */

/* Sets the output flag when func_80034FD0 returns nonzero. */
void func_80034F9C(s8 *result_flag) {
    if (func_80034FD0(result_flag) != 0) {
        *result_flag = 1;
    }
}
