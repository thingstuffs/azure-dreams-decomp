#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern s32 D_80017768;
/* Stores 1 in D_80017768. */
void initialize_dungeon_region_records(void) { D_80017768 = 1; }
