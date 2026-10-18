#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017800[];
extern void *D_800178D0;
void check_scene_state_counter_threshold(void) { D_800178D0 = D_80017800; }
