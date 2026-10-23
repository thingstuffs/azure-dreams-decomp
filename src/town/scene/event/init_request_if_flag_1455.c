#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
typedef struct Town654Request { u8 prefix[0x18]; s16 flag_18; } Town654Request;
extern s32 func_8001868C(s32 flag);
extern void initialize_state_two_entries_pointer(s32 flag);
extern void func_800177CC(Town654Request *, s32);

/*
 * Initializes the request entry pointers from flag_18 while F_niko_selro_asa is set, then
 * processes the request and parameter through func_800177CC.
 */
void init_request_if_flag_1455(Town654Request *request, s32 parameter)
{
    if (func_8001868C(F_niko_selro_asa) != 0) initialize_state_two_entries_pointer(request->flag_18);
    func_800177CC(request, parameter);
}
