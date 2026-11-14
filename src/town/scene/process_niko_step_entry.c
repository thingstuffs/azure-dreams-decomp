#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/player/state.h"
typedef struct Town654Request { u8 prefix[0x18]; s16 flag_18; } Town654Request;

/*
 * Sets the request's script flag (flag_18) while F_s04_niko_step is set, then passes the request and
 * parameter to process_checked_entry.
 */
void process_niko_step_entry(Town654Request *request, s32 parameter)
{
    if (get_script_flag_mask(F_s04_niko_step) != 0) set_script_flag_bit(request->flag_18);
    process_checked_entry(request, parameter);
}
