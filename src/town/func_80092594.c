#include "common.h"

extern void *D_800FE490[];

void func_8008FCF4(void *arg0) {
    *(void **)arg0 = D_800FE490;
    *((void **)arg0 + 1) = *((void **)D_800FE490 + 1);
    *((void **)*((void **)D_800FE490 + 1)) = arg0;
    *((void **)D_800FE490 + 1) = arg0;
}
