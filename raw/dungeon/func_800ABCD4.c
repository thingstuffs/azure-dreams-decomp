#include "common.h"

void *func_800B1434(void *arg0, void *arg1) {
    void *temp_a2 = arg1 + 8;
    void *temp_v1 = arg0 + 8;

    do {
        *(s32 *)arg0 = *(s32 *)arg1;
        *(s32 *)(arg0 + 4) = *(s32 *)(arg1 + 4);
        *(s32 *)(arg0 + 8) = *(s32 *)(arg1 + 8);
        arg0 += 0xC;
        if (*(s8 *)arg1 < 0) {
            return arg0;
        }
        temp_v1 += 0xC;
        temp_a2 += 0xC;
        arg1 += 0xC;
    } while (1);
}
