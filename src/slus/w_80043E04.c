#include "shared/runtime_dispatch.h"
#include "slus/slot_transition.h"

/* Updates the frame, then allocates a slot and installs func_80043E60 if signaled, otherwise calls func_8003D92C. */
void func_80043E04(void) {
    render_object_scene_frame();
    if (D_80082E60.unk_0E != 0) {
        D_80081500 = reserve_runtime_slot(6, 8);
        set_scene_phase_callback((int) func_80043E60);
    } else {
        func_8003D92C();
    }
}
