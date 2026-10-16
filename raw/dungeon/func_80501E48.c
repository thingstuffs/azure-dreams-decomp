#include "common.h"
#include "m2c_compat.h"

void func_80019648(void) {
    s32 temp_v0_2;
    s8 temp_v0;

    temp_v0 = *(s8 *)0x80012D52;
    if (temp_v0 >= 0) {
        temp_v0_2 = temp_v0 * 4;
        if (*(0x800121E8 + temp_v0_2) == 2) {
            *(0x800121E8 + temp_v0_2) = 0x39U;
        }
    }
}
