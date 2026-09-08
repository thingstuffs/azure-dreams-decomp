#include "common.h"

extern s32 D_800D0C48[];
extern s32 D_80100DE0[];

/* Town script command 216: copy two values into script state slots 9 and 10. */
void func_800A510C(void) {
    D_80100DE0[9] = D_800D0C48[0];
    D_80100DE0[10] = D_800D0C48[1];
}
