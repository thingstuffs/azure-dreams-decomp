#include "common.h"
#include "m2c_compat.h"

extern s32 D_800178D8;
/* Stores 1 in D_800178D8. */
void set_scene_flag_word(void) { D_800178D8 = 1; }
