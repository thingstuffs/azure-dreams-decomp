#include "common.h"

extern s8 D_80082A39;
extern s32 D_80110EC0;

/* Clear D_80110EC0 and D_80082A39. */
void townClearGlobal80110EC0Global80082A39(void) {
    D_80110EC0 = 0;
    D_80082A39 = 0;
}
