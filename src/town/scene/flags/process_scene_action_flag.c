#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void func_8001611C(s32 value_18e44, s32 value_18e48); /* placed copy of set_global_entry_pair */
extern s32 func_80017D9C(s32, s32);
extern void func_80018854(s32); /* placed copy of set_script_flag_bit */
extern s16 scene_request_flag_id[];

/* Process the object action when flag 0x510 is set, otherwise update flag 0x511. */
s32 process_scene_action_flag(s32 object, s32 context) {
    func_8001611C(object, context);
    if (func_8001894C(F_sbs07_pad25) != 0) {
        return func_80017D9C(object, context);
    }
    if (func_8001894C(scene_request_flag_id[0]) == 0) {
        func_80018854(F_sbs07_pad26);
    }
    return 0;
}
