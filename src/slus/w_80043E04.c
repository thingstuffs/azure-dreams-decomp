#include "shared/runtime_dispatch.h"
#include "slus/slot_transition.h"

/* Updates the frame, then allocates a slot and installs func_80043E60 if signaled, otherwise calls func_8003D92C. */
void func_80043E04(void) {
    renderObjectSceneFrame();
    if (D_80082E60.unk_0E != 0) {
        D_80081500 = reserveRuntimeSlot(6, 8);
        setScenePhaseCallback((int) func_80043E60);
    } else {
        func_8003D92C();
    }
}
