#include "common.h"

extern s32 D_80100D20;

/* Clears D_80100D20. */
void townClearGlobal80100D20(void) {
    D_80100D20 = 0;
}
