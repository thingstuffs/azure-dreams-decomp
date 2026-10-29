#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

/* Run town service callback 0x280 with (0xB1). */
void initialize_context_entry_tables_variant_2(void) {
    town_scene_root->services->callback_280(0xB1);
}
