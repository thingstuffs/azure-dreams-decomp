#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene.h"
/*
 * Initializes the request entry pointers from flag_18 while F_niko_selro_asa is set, then
 * processes the request and parameter through func_800177CC.
 */
void process_niko_selro_asa_request(TownObjectSet *request, s32 parameter)
{
    if (get_script_flag_mask(F_niko_selro_asa) != 0) set_script_flag_bit(request->entry_flag);
    process_checked_entry(request, parameter);
}
