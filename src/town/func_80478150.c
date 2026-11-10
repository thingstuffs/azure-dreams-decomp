#include "common.h"
#include "town/scene/data_access.h"
#include "town.h"
#include "town/data.h"


/* Set the D_80019BC4 flag. */
void request_scene_rescan_a(void) {
    scene_handler_ready = 1;
}
