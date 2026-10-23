#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



void func_800174CC();                            /* extern */
extern M2C_UNK D_80019814;
extern M2C_UNK D_80019884;
extern s32 D_80019AF8;
extern void *scene_current_cell_pointer;

/* Initializes data pointers and computes the selected eight-byte entry address. */
void init_entry_pointers(void) {
    func_800174CC();
    scene_current_cell_pointer = &D_80019814;
    D_80019AF8 = ((s32)town_scene_root->event_data)
    + (town_scene_root->entry_index * 8);
    ((TownPositionState *)town_scene_root->position)->unk_40 = &D_80019884;
}
