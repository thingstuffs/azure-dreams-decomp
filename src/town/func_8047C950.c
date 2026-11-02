#include "common.h"
#include "town/scene/data_access.h"
#include "town.h"
#include "town/data.h"

/* Set D_80019BC4 to 1. */
void request_scene_rescan_b(void) {
    scene_handler_ready = 1;
}
