#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/resource.h"
#include "town/scene/record_actions.h"
extern void update_entry_flags(void);
void func_8001A554(s32);
void func_8001A5CC(s32);
extern s32 func_8001A64C(s32 flagIndex);


/* Advance the town scene: raise 0x94B, then hand back to the scene callback unless flag 0x943 and the step check both pass. */
s32 advance_town_scene_raise_hand(Rec_func_800165F4_arg0 *kind, s32 value) {
    set_script_flag_94c();
    initialize_resources_assigns_pointer_lookup();
    func_8001A554(F_sbs32_pad33);
    if (func_8001A64C(F_sbs32_pad25) == 0) {
        town_scene_root->services->callback_2F8(0xE, 0x200);
        return 0;
    }
    update_entry_flags();
    if (func_8001991C(kind, value) == 0) {
        town_scene_root->services->callback_2F8(0xE, 0x200);
        return 0;
    }
    func_8001A5CC(F_sbs32_pad25);
    return 1;
}
