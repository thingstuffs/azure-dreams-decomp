#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern M2C_UNK D_80019890;


/* Dispatches IDs 0x3EB and 0x631, then invokes object callbacks with 0 and &D_80019890. */
void set_paty_kuinige_and_call_services(void) {
    set_script_flag_bit(F_paty_kuinige);
    clear_script_flag_bit(F_sbs14_pad13);
    ((s32 (*) (s32))town_scene_root->services->callback_084)(0);
    ((s32 (*) (s32 *))town_scene_root->services->callback_218)(&D_80019890);
}
