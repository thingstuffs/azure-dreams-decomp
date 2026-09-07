#include "common.h"

s32 func_8009F71C(void *arg0, s32 arg1) {
    s32 i = 0;

    if (arg1 > 0) {
        do {
            if (((u8 *)arg0)[1] == 0) {
                return i;
            }
            i++;
            arg0 += 4;
        } while (i < arg1);
    }
    return -1;
}
