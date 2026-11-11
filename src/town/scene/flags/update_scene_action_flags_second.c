#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/hooks.h"

typedef struct S_func_804B80D0_1 {
    u8 pad_00[2];
    u8 unk_02;
} S_func_804B80D0_1;

extern s16 scene_request_flag_id;

/* Update action flags from the active entry and check whether the action is allowed. */
s32 update_scene_action_flags(s32 object, s32 context) {
    s32 action_allowed;

    set_global_entry_pair(object, context);
    if (get_script_flag_mask(scene_request_flag_id) == 0) {
        set_script_flag_bit(F_sbs07_pad26);
        if (((S_func_804B80D0_1 *)
             ((town_scene_root->entry_index * 8) +
              ((u8 *)town_scene_root->event_data)))->unk_02 == 0) {
            clear_script_flag_bit(F_sbs07_pad29);
        }
    }
    if (get_script_flag_mask(F_sbs07_pad29) == 0) {
        action_allowed = get_script_flag_mask(Fp_pool_open) == 0;
    } else {
        action_allowed = 1;
    }
    return action_allowed;
}
