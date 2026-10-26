#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"





/* Invoke the callback with code 8 when checks 0x1200 and 0x1201 both return zero. */
void invoke_code_8_when_flags_clear(void) {
    if ((get_script_flag_mask(Fp_bibian_pool_event) == 0) && (get_script_flag_mask(Fp_mia_pool_event) == 0)) {
        town_scene_root->services->callback_1E8(8);
    }
}
