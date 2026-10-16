#include "shared/runtime_dispatch.h"
#include "slus/slot_transition.h"

/* Runs the state update, then allocates a slot and advances the callback if enabled, or invokes the fallback. */
void func_80041BE4(void)
{
    renderSceneFrameWithTiming();
    if (D_80082E60.unk_0E != 0) {
        if (D_80083120[D_800814E8].type == 0) {
            D_800814E8 = reserveRuntimeSlot(6, 8);
        }
        setScenePhaseCallback((int) func_80041C64);
    } else {
        func_8003D92C();
    }
}
