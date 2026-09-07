#include "common.h"

/* Multiplies a volatile stack value by 13 sixty times, then discards the result. */
void func_8005D730(void) {
    volatile s32 iteration;
    volatile s32 product;

    product = 13;
    for (iteration = 0; iteration < 60; iteration++) {
        product = product * 13;
    }
}
