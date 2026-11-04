#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/motion.h"
#include "town/data.h"

extern s32 D_80018EAC;
extern s32 D_80018EC4;

/* Update flag 0x681 when triggered and dispatch the corresponding record. */
void pass_2(s32 dispatch_context, s32 unused, s32 dispatch_arg)
{
    s8 *callback_table;

    if (check_callback_record_bytes(1, 8) != 0) {
        callback_table = (s8 *)town_scene_root;
        callback_table = *(s8 **)(callback_table + 0x20);
        (*(void (**)(s32))(callback_table + 0x78))(0);
        set_script_flag_bit(F_sbs16_pad07);
    } else {
        if (get_script_flag_mask(F_sbs16_pad07) == 0) {
            apply_entry_position(&D_80018EAC, &scene_request_context, dispatch_context, dispatch_arg);
            return;
        }
    }

    apply_entry_position(&D_80018EC4, &scene_request_context, dispatch_context, dispatch_arg);
}
