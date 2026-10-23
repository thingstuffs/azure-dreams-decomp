#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80019054[];

/* Run town service callback 0X218 with this module's record D_80019054 (this TOWN module's copy of the town/func_8032D78C wrapper). */
void initialize_context_entry_tables_variant_1(void) {
    town_scene_root->services->callback_218(D_80019054);
}
