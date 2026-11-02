#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene/resource.h"
#include "town/player/state.h"
#include "town/scene.h"



void select_handler_by_state_code_0x798(s32 slotIndex);
extern M2C_UNK D_8002116C;


/* Initializes resources and assigns their data pointer when lookup succeeds. */
void initialize_resources_assigns_pointer_lookup(void) {
    s32 resource_id;

    resource_id = find_entry_index_by_grid_bytes(0xD, 6);
    if (resource_id != -1) {
        select_handler_by_state_code_0x798(resource_id);
        set_script_flag_bit(F_sbs32_pad02);
        set_script_flag_bit(F_sbs32_pad03);
        set_script_flag_bit(F_sbs32_pad04);
        set_script_flag_bit(F_sbs32_pad05);
        set_script_flag_bit(F_sbs32_pad06);
        set_script_flag_bit(F_okami_give_cape);
        clear_script_flag_bit(F_sbs32_pad25);
        town_scene_root->position->unk_40 = &D_8002116C;
    }
}
