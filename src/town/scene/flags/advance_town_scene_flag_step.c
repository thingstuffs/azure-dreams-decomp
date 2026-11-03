#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/resource.h"
#include "shared/town_root.h"

extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */
extern void clear_script_flag_bit(s32);
extern s32 get_script_flag_mask(s32);

typedef void (*Callback)(s32, s32);

/* Advance the town scene: clear flag 0x943 when it is set and the step check passes, otherwise hand back to the scene callback. */
s32 advance_town_scene_flag_step(s32 kind, s32 value) {
    set_script_flag_94c();
    initialize_resources_assigns_pointer_lookup();

    if (get_script_flag_mask(F_sbs32_pad25) != 0) {
        func_80019988();
        if (apply_selected_entry_values(kind, value) != 0) {
            clear_script_flag_bit(F_sbs32_pad25);
            return 1;
        }
    }

    ((Callback)(town_scene_root->services->callback_2F8))(0xE, 0x200);
    return 0;
}
