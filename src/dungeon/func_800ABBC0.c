#include "common.h"

void func_800B1320(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *temp_a3;

    temp_a3 = arg0 + 3;
loop:
        temp_a3[-1] += arg1;
        temp_a3[0] += arg2;
        if (*(s8 *)arg0 < 0) {
            goto done;
        }
        temp_a3 += 0xC;
        arg0 += 0xC;
        goto loop;
done:
    ;
}
