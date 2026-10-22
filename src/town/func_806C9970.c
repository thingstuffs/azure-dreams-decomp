#include "common.h"

extern s32 dispatch_event_63_a_through_193_e_0(s32, s32);
s32 check_event_dispatch_success(s32 grid_y, s32 grid_x) { return (dispatch_event_63_a_through_193_e_0(grid_y, grid_x) != -1); }
