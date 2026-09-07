#include "common.h"

void func_800B1400(u8 *arg0, s32 arg1) {
    for (;;) {
        arg0[1] = arg0[1] | arg1;
        if ((s8)arg0[0] < 0) {
            return;
        }
        arg0 += 12;
    }
}
