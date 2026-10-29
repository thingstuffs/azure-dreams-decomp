#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern u8 D_80017B10[];
/* Returns the current value of D_80017B10. */
void *get_scene_record_pointer(void) { return D_80017B10; }
