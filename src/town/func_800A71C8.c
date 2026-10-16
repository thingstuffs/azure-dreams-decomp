#include "common.h"

extern s32 D_80100DB8[];
extern s32 D_80100DE0[];

extern void townInitializeControlBlock(s32 *control);
extern void townInitializePairedStateCallbacks(s32 *state);
extern void townClearTransitionWord(void);

/* Initialize both state blocks and finish setup. */
void func_800A4928(void) {
    s32 *state = D_80100DB8;

    townInitializeControlBlock(D_80100DE0);
    townInitializePairedStateCallbacks(state);
    townClearTransitionWord();
}
