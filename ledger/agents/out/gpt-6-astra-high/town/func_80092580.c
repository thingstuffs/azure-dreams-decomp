#include "common.h"

extern void *D_800FE490[];

/* Sets the first two pointers in D_800FE490 to the array itself. */
void func_8008FCE0(void) {
    D_800FE490[0] = D_800FE490;
    D_800FE490[1] = D_800FE490;
}
