#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
typedef struct Town654Request { u8 prefix[0x18]; s16 flag_18; } Town654Request;
extern s32 func_8001868C(s32 flag);
extern void initialize_state_two_entries_pointer(s32 flag);
extern void func_800177CC(Town654Request *, s32);

/*
 * Initializes the request entry pointers from flag_18 while F_s04_niko_step is set, then processes
 * the request and parameter through func_800177CC.
 */
void reset_dungeon_runtime_state(Town654Request *request, s32 parameter)
{
    if (func_8001868C(F_s04_niko_step) != 0) initialize_state_two_entries_pointer(request->flag_18);
    func_800177CC(request, parameter);
}
