#include "common.h"
#include "town/scene/data_access.h"

extern s32 D_80019BC4;

/* Set D_80019BC4 to 1. */
void request_scene_rescan_b(void) {
    D_80019BC4 = 1;
}
