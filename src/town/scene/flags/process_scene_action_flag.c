#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void set_global_entry_pair(s32 value_18e44, s32 value_18e48); /* placed copy of set_global_entry_pair */
extern s32 apply_selected_entry_values(s32, s32);
extern s16 scene_request_flag_id[];

/* Process the object action when flag 0x510 is set, otherwise update flag 0x511. */
s32 process_scene_action_flag(s32 object, s32 context) {
    set_global_entry_pair(object, context);
    if (get_script_flag_mask(F_sbs07_pad25) != 0) {
        return apply_selected_entry_values(object, context);
    }
    if (get_script_flag_mask(scene_request_flag_id[0]) == 0) {
        set_script_flag_bit(F_sbs07_pad26);
    }
    return 0;
}
