#include "common.h"
#include "town/scene/script_hooks.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/data.h"


s32 copy_and_terminate_coordinate_entries(void *);
s8 *clear_bytes(s8 *buffer, s32 length); /* Unprototyped: retail call passes more arguments than the callee reads */
extern s8 D_80019440[];

/* Prepare D_80019440 for the callback and store its result in D_80019540. */
s32 prepare_and_register_entry_buffer(void) {
    clear_bytes(D_80019440, 0x100);
    copy_and_terminate_coordinate_entries(&D_80019440);
    return scene_registered_entry_handle = town_scene_root->services->callback_068(0, 1, 2, &D_80019440);
}
