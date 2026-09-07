#include "common.h"

extern s32 func_8004A618(void *arg0);
extern s8 D_800D1074[];
extern s32 D_800D1080[];

s32 func_800A9A38(u8 *arg0) {
    s32 index;
    s32 value;

    if (D_800D1074[0] != -1) {
        index = 0;
        do {
            if (D_800D1074[index] == arg0[1]) {
                value = func_8004A618(arg0);
                if (value < D_800D1080[0]) {
                    return 0;
                }
                if (value < D_800D1080[1]) {
                    return 1;
                }
                return 2;
            }
            index++;
        } while (D_800D1074[index] != -1);
    }

    return 3;
}
