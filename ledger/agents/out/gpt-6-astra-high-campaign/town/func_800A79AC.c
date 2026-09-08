#include "common.h"

extern s32 D_800D0C48[];
extern s32 D_80100DE0[];

/* tcame_return: copy the saved camera values into script state slots 9 and 10. */
void func_800A510C(void) {
    D_80100DE0[9] = D_800D0C48[0];
    D_80100DE0[10] = D_800D0C48[1];
}
