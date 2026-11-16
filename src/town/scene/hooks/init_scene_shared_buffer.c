#include "common.h"
#include "m2c_compat.h"

extern u8 D_800175B8[];
extern void *D_8001766C;
/* Stores D_800175B8 in D_8001766C. */
void init_scene_shared_buffer(void) { D_8001766C = D_800175B8; }
