#include "common.h"

extern s32 D_8001E954[];
extern s32 func_8001C5CC(void);

s32 func_8001C288(void) {
    s32 value;
    if (D_8001E954[0] == 0) {
        return 0;
    }
    value = func_8001C5CC();
    if (value != 0) {
        return 2;
    }
    return 1;
}
