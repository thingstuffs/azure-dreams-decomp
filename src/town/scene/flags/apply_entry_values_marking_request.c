#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

s32 apply_selected_entry_values(s32, s32);
extern s16 scene_request_flag_id;

/* Updates flag 0x511 when the selected flag is clear, then processes the request. */
void apply_entry_values_marking_request(s32 request_id, s32 request_arg) {
    if (get_script_flag_mask(scene_request_flag_id) == 0) {
        set_script_flag_bit(F_sbs07_pad26);
    }
    apply_selected_entry_values(request_id, request_arg);
}
