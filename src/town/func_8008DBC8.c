#include "common.h"

extern s32 func_8008B2E4(s32 arg0);

extern u8 D_800CF828[15];
extern s32 D_800CF838[16];

s32 func_8008B328(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        if (func_8008B2E4(D_800CF838[D_800CF828[i]]) != 0) {
            return 1;
        }
    }

    return 0;
}
