#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern s32 D_80017AA0;
/* Request another pass through the eligible entries in town bank 671800. */
void set_selection_index_1(void) { D_80017AA0 = 1; }
