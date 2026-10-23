#include "common.h"
#include "town/scene/data_access.h"

extern s32 D_8001B328;

/* Set the D_8001B328 flag. */
void request_scene_rescan_c(void) {
    D_8001B328 = 1;
}
