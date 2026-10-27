#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void store_supplied_values(s32, s32);
extern s32 func_80017D9C(s32, s32);
extern void call_helper_with_fixed_id_0x118a(s32);
extern s16 scene_request_flag_id[];

/* Process the object action when flag 0x510 is set, otherwise update flag 0x511. */
s32 process_scene_action_flag(s32 object, s32 context) {
    store_supplied_values(object, context);
    if (func_8001894C(F_sbs07_pad25) != 0) {
        return func_80017D9C(object, context);
    }
    if (func_8001894C(scene_request_flag_id[0]) == 0) {
        call_helper_with_fixed_id_0x118a(F_sbs07_pad26);
    }
    return 0;
}
