#include "common.h"

extern u8 D_80080EA8[];
extern u8 D_800CF828[];
extern void *D_800CF838[];

s32 func_8008B3AC(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        if (D_800CF838[D_800CF828[i]] == D_80080EA8) {
            return i;
        }
    }

    return -1;
}
