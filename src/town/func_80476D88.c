#include "common.h"

extern s32 D_80019BB0;

/* Returns whether D_80019BB0 is nonzero. */
s32 townIsGlobalFlag19BB0Set(void) {
    return D_80019BB0 != 0;
}
