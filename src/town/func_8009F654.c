#include "common.h"

extern s32 *D_801007F4;
extern s32 D_80100900[];

/* Initializes the shared data pointer, clears its first word and returns it. */
s32 *func_8009CDB4(void) {
    D_801007F4 = D_80100900;
    D_80100900[0] = 0;
    return D_80100900;
}
