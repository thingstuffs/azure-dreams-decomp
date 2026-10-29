#include "common.h"
#include "town/scene/script_hooks.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern u8 D_80017800[];
extern void *D_800178D0;
/* Stores D_80017800 in D_800178D0. */
void *bind_scene_pointer(void) { return D_800178D0 = D_80017800; }
