#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/resource.h"
#include "town/scene/record_actions.h"
#include "town/player/state.h"
extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */

/* Advance the town scene: raise 0x94B, then hand back to the scene callback unless flag 0x943 and the step check both pass. */
s32 advance_town_scene_raise_hand(Rec_func_800165F4_arg0 *kind, s32 value) {
    set_script_flag_94c();
    initialize_resources_assigns_pointer_lookup();
    set_script_flag_bit(F_sbs32_pad33);
    if (get_script_flag_mask(F_sbs32_pad25) == 0) {
        town_scene_root->services->callback_2F8(0xE, 0x200);
        return 0;
    }
    func_80019988();
    if (apply_selected_entry_values(kind, value) == 0) {
        town_scene_root->services->callback_2F8(0xE, 0x200);
        return 0;
    }
    clear_script_flag_bit(F_sbs32_pad25);
    return 1;
}
