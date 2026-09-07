#include "common.h"

#include "common.h"

s32 func_80034FD0();                                /* extern */

void func_80034F9C(s8 *arg0) {
    if (func_80034FD0() != 0) {
        *arg0 = 1;
    }
}
