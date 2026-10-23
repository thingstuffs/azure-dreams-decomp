#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


s32 func_80016A38(void *);
void advance_town_events_and_dispatch_entry();
extern M2C_UNK D_80019440;
extern s32 scene_registered_entry_handle;

/* Prepare D_80019440 for the callback and store its result in D_80019540. */
void prepare_and_register_entry_buffer(void) {
    advance_town_events_and_dispatch_entry(&D_80019440, 0x100);
    func_80016A38(&D_80019440);
    scene_registered_entry_handle = town_scene_root->services->callback_068(0, 1, 2, &D_80019440);
}
