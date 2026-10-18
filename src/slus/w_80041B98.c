#include "slus/slot_transition.h"

/* Runs the state update and registers the next callback when the current slot becomes inactive. */
void func_80041B98(void)
{
    render_scene_frame_with_timing();
    if (D_80083120[D_800814E8].type == 0) {
        set_scene_phase_callback((int)func_80041BE4);
    }
}
