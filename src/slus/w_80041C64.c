#include "slus/slot_transition.h"

/* Runs the state update, then sets flag bit 0 and invokes sceneSavePreviousModeAndResetCallbacks when the current slot is inactive. */
void func_80041C64(void)
{
    renderSceneFrameWithTiming();
    if (D_80083120[D_800814E8].type == 0) {
        D_80082E60.field_0 |= 1;
        sceneSavePreviousModeAndResetCallbacks();
    }
}
