#include "common.h"
#include "town/scene/state_data.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/service.h"


extern M2C_UNK D_800179FC;

/* Dispatches the table entry selected by the current index. */
void run_scene_service_230_by_index(void) {
    town_scene_root->services->callback_230(*((s32 *)((s8 *)&D_800179FC + scene_selection_index * 4)));
}
