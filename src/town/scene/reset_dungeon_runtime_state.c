#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/player/state.h"
typedef struct Town654Request { u8 prefix[0x18]; s16 flag_18; } Town654Request;

/*
 * Initializes the request entry pointers from flag_18 while F_s04_niko_step is set, then processes
 * the request and parameter through func_800177CC.
 */
void reset_dungeon_runtime_state(Town654Request *request, s32 parameter)
{
    if (get_script_flag_mask(F_s04_niko_step) != 0) set_script_flag_bit(request->flag_18);
    process_checked_entry(request, parameter);
}
