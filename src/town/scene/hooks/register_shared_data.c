#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_dispatch_data.h"
#include "town/scene/hooks.h"
#include "town/data.h"
#include "town.h"

/* Initialize the shared data and store the mode-2 callback result. */
void register_shared_data(void) {

    initialize_packed_record_defaults(&D_80018AE8);

    scene_registered_data_handle = town_scene_root->services->callback_068(0, 0, 2, &D_80018AE8);
}
