#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/scene/object.h"
#include "town/scene/hooks.h"

extern s16 D_800160B0;
extern s16 repeat_entry_flag_id;
extern s32 *installed_object_sets;
extern M2C_UNK D_80016E48;
extern M2C_UNK D_80016F88;
extern s32 D_80016FC8;
extern M2C_UNK D_8001700C;

/* Initialize shared state and attach its data pointers. */
void init_runtime_pointers_from_shared_buffer(void) {
    copy_flag_state_to_target(D_800160B0, repeat_entry_flag_id);
    install_object_set_table();
    build_object_set_and_select_lists_rev_b(installed_object_sets, &D_80016E48, &D_80016F88);
    town_scene_root->unk_34 = &D_80016FC8;
    town_scene_root->unk_28 = &D_80016E48;
    town_scene_root->unk_2C = &D_8001700C;
}
