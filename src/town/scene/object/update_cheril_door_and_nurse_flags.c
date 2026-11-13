#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"

extern s32 D_80018FEC;
extern s32 *D_800190D8;
extern s32 D_80019A74;

/* Initializes state pointers and updates flags based on the current state. */
void update_cheril_door_and_nurse_flags(void) {
    D_800190D8 = &D_80018FEC;
    set_script_flag_bit(F_sb24_door_dummy);
    clear_script_flag_bit(F_sb24_nd_dummy0);

    if (get_script_flag_mask(Ft_name_to_cheril) == 0) {
        clear_script_flag_bit(F_sb24_door_dummy);
        set_script_flag_bit(F_sb24_nd_dummy0);
        town_scene_root->position->unk_40 = &D_80019A74;
    }

    if (get_script_flag_mask(Fp_cheriru_kangofu) != 0) {
        clear_script_flag_bit(F_kangofu);
        return;
    }

    set_script_flag_bit(F_kangofu);
}
