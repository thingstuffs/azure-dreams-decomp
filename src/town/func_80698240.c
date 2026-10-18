#include "common.h"

extern s32 func_800171FC(void);
s32 advance_town_scene_flag_step(void) { return 20 - func_800171FC(); }
