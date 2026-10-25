#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_dispatch_data.h"


void * dispatch_event_d_8_a(void *record);
extern s32 scene_registered_data_handle;

/* Initialize the shared data and store the mode-2 callback result. */
void register_shared_data(void) {

    dispatch_event_d_8_a(&D_80018AE8);

    scene_registered_data_handle = town_scene_root->services->callback_068(0, 0, 2, &D_80018AE8);
}
