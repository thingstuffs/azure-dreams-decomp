#include "common.h"
#include "m2c_compat.h"

extern s32 D_800178A4;
/* Returns the address of D_800178A4. */
void *get_scene_entry_buffer(void) { return &D_800178A4; }
