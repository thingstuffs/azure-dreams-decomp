#include "common.h"

extern s32 D_8009EB54[4];

s32 func_8001B268(void) {
    s32 *value = &D_8009EB54[1];

    if (*(s32 *)0x804094EC != 0) {
        value++;
    }
    return *value;
}
