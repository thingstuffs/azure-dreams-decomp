/* Relink of matched town/func_80476D88; every changed retail word is a paired relocation. */
#define townIsGlobalFlag19BB0Set func_80017D88
#include "common.h"

extern s32 D_80019BB0;

/* Returns whether D_80019BB0 is nonzero. */
s32 func_80017D88(void) {
    return D_80019BB0 != 0;
}
