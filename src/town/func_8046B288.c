#include "common.h"

extern s32 D_8001E954[];
extern s32 func_8001C5CC(void);

s32 func_8001C288(void) {
    s32 value;

    if (D_8001E954[0] != 0) {
        value = func_8001C5CC();
        if (value == 0) {
            return 1;
        }
        return 2;
    }
    return 0;
}

/* MECHANISM: The rowbase jump to 0x8001C2BC is the local return join, not a callee.
   A named call-result local induces the retail v0-to-v1 copy before its test;
   an explicit zero-result arm selects the retail branch polarity and delay slots. */
