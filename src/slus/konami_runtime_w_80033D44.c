#include "slus/gp_shared_8099c.h"

/* obj_disp23_cancel_sw_set: sets the display cancellation switch and returns it. */
s32 obj_disp23_cancel_sw_set(s32 cancel_switch)
{
    D_8008099C = cancel_switch;
    return cancel_switch;
}
