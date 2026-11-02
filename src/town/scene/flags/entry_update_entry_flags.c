#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/record_actions.h"
#include "town/player/state.h"

typedef void (*TownCallback)(s32, s32);



extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */

/* Advance the town scene: clear flag 0x943 when it is set and the step check passes, otherwise hand back to the scene callback. */
s32 update_and_test_pending_entry_flags(Rec_func_800165F4_arg0 *kind, s32 value) {
    Rec_D_80016000 *root;

    set_script_flag_94c();
    if (get_script_flag_mask(F_sbs32_pad25) != 0) {
        func_80019988();
        if (apply_selected_entry_values(kind, value) != 0) {
            clear_script_flag_bit(F_sbs32_pad25);
            return 1;
        }
    }

    root = town_scene_root;
    ((TownCallback)root->services->callback_2F8)(0xF, 0x200);
    return 0;
}
