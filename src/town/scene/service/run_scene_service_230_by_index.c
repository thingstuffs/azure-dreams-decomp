#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


extern M2C_UNK D_800179FC;
extern s16 scene_selection_index;

/* Dispatches the table entry selected by the current index. */
void run_scene_service_230_by_index(void) {
    D_80016000->unk_20->callback_230(*((s32 *)((s8 *)&D_800179FC + scene_selection_index * 4)));
}
