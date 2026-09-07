#include "common.h"

extern void *D_800FE490[];

void func_8008FCE0(void) {
    D_800FE490[0] = D_800FE490;
    *((void **) D_800FE490 + 1) = D_800FE490;
}
