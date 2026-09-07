#include "common.h"

/* Dead-store loop: computes x = x*13 repeatedly on a stack local, result unused. */
void func_8005D730(void) {
    volatile s32 i;
    volatile s32 x;

    x = 13;
    for (i = 0; i < 60; i++) {
        x = x * 13;
    }
}
