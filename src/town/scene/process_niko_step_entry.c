#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/player/state.h"
/*
 * Sets the request's script flag (flag_18) while F_s04_niko_step is set, then passes the request and
 * parameter to process_checked_entry.
 */
void process_niko_step_entry(TownObjectSet *request, s32 parameter)
{
    if (get_script_flag_mask(F_s04_niko_step) != 0) set_script_flag_bit(request->entry_flag);
    process_checked_entry(request, parameter);
}
