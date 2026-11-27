#include "common.h"
#include "m2c_compat.h"
#include "town.h"

extern s32 scene_entry_rescan_requested;
void set_scene_entry_flag_a(void) { scene_entry_rescan_requested = 1; }
