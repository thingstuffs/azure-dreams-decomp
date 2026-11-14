#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"

typedef void (*TownCallback)(s32, s32);

// Dispatches the town callback if check 0x1068 fails, otherwise issues commands 0x94F and 0x93E.
s32 start_message_unless_vivian_fine(void) {
    s32 checkPassed;

    set_script_flag_sbs32_pad34();

    if (get_script_flag_mask(Frg_vivian_fine) == 0) {
        ((TownCallback)(town_scene_root->services->callback_2F8))(0xE, 0x200);
        checkPassed = 0;
    } else {
        set_script_flag_bit(F_sbs32_pad37);
        set_script_flag_bit(F_sbs32_pad20);
        checkPassed = 1;
    }
    return checkPassed;
}
