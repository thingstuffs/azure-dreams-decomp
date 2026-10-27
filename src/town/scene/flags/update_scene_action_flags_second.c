#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/script_flags.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_func_804B80D0_1 {
    u8 pad_00[2];
    u8 unk_02;
} S_func_804B80D0_1;

extern void func_8001611C(s32 value_18e44, s32 value_18e48); /* placed copy of set_global_entry_pair */
extern void func_80018854(s32); /* placed copy of set_script_flag_bit */
extern s32 func_800188CC(s32);
extern s16 scene_request_flag_id;

/* Update action flags from the active entry and check whether the action is allowed. */
s32 update_scene_action_flags(s32 object, s32 context) {
    s32 action_allowed;

    func_8001611C(object, context);
    if (func_8001894C(scene_request_flag_id) == 0) {
        func_80018854(F_sbs07_pad26);
        if (((S_func_804B80D0_1 *)
             ((town_scene_root->entry_index * 8) +
              ((u8 *)town_scene_root->event_data)))->unk_02 == 0) {
            func_800188CC(F_sbs07_pad29);
        }
    }
    if (func_8001894C(F_sbs07_pad29) == 0) {
        action_allowed = func_8001894C(Fp_pool_open) == 0;
    } else {
        action_allowed = 1;
    }
    return action_allowed;
}
