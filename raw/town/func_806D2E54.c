#include "common.h"

extern s32 func_80016D78(s16);

s32 func_80016654(s16 *arg0) {
    s16 *p = arg0;

    while (*p != 0) {
        if (func_80016D78(*(u16 *)p) == 0) {
            break;
        }
        p++;
    }

    return *p == 0;
}
