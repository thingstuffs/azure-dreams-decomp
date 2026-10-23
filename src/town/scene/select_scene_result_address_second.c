#include "common.h"
#include "m2c_compat.h"

extern s32 D_800174DC;
/* Stores 1 in D_800174DC. */
void select_scene_result_address(void) { D_800174DC = 1; }
