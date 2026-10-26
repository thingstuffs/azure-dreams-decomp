#include "town/scene.h"

extern u8 D_8001C33C[];
extern u8 D_8001E6B4[];
extern s32 apply_record_value_when_enabled(SquareSceneEntry *, s32);
extern void *dispatch_through_table_bb_5_c(SquareSceneEntry *, s32, s32);
extern s32 process_request_and_notify(SquareSceneEntry *, s32);
extern void *dispatch_through_table_bb_64(SquareSceneEntry *, s32, s32);
extern s32 apply_record_value_for_either_flag(SquareSceneEntry *, s32);
extern void *dispatch_or_override_for_flag_1390(SquareSceneEntry *, s32, s32);
extern s32 apply_gate_5211_flag_entry(SquareSceneEntry *, s32);
extern void *dispatch_through_table_bb_74(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_b(SquareSceneEntry *, s32);
extern void *dispatch_entry_or_return_override(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_c(SquareSceneEntry *, s32);
extern void *is_pair_result_valid_b(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_d(SquareSceneEntry *, s32);
extern void *func_8001793C(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_e(SquareSceneEntry *, s32);
extern void *dispatch_entry_or_process_fallback(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_f(SquareSceneEntry *, s32);
extern void *select_square_entry_or_fallback(SquareSceneEntry *, s32, s32);
extern s32 apply_gate_5003_flag_entry(SquareSceneEntry *, s32);
extern void *func_80017B5C(SquareSceneEntry *, s32, s32);
extern void *func_80017C34(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_g(SquareSceneEntry *, s32);
extern void *select_square_entry_or_alternate(SquareSceneEntry *, s32, s32);
extern s32 forward_context_request_to_handler_c_68(SquareSceneEntry *, s32);
extern s32 func_80017D74(SquareSceneEntry *, s32);
extern void *invoke_handler_with_code_798(SquareSceneEntry *, s32, s32);
extern s32 func_80017E34(SquareSceneEntry *, s32);
extern void *dispatch_through_table_bbc_4(SquareSceneEntry *, s32, s32);
extern void *get_shared_entry_buffer(SquareSceneEntry *, s32, s32);
extern s32 return_zero_fn(SquareSceneEntry *, s32);
extern s32 get_script_flag_mask(s32);
extern void set_current_entry_script_flag(void);
extern s32 apply_selected_entry_values(void *, s32);
extern void set_script_flag_bit(s32);
extern s32 process_checked_entry(void *, s32);

s32 apply_gate_5000_flag_entry(SquareSceneEntry *entry, s32 entry_index) {
    if (get_script_flag_mask(5000) != 0) {
        set_script_flag_bit(entry->unk_18);
    }
    return process_checked_entry(entry, entry_index);
}

/* Complete choice array, including its terminal fallback record. */
TownSceneChoice square_flag_choices[17] = {
    { apply_record_value_when_enabled, get_shared_entry_buffer, D_8001C33C, 3412, 0 },
    { process_request_and_notify, dispatch_through_table_bb_5_c, D_8001E6B4, 3413, 0 },
    { apply_record_value_for_either_flag, dispatch_through_table_bb_64, D_8001E6B4, 3414, 0 },
    { apply_gate_5000_flag_entry, dispatch_or_override_for_flag_1390, D_8001E6B4, 3415, 0 },
    { apply_gate_5211_flag_entry, get_shared_entry_buffer, D_8001C33C, 3416, 0 },
    { forward_context_request_to_handler_b, dispatch_through_table_bb_74, D_8001E6B4, 3417, 0 },
    { forward_context_request_to_handler_c, dispatch_entry_or_return_override, D_8001E6B4, 3418, 0 },
    { forward_context_request_to_handler_d, is_pair_result_valid_b, D_8001E6B4, 3419, 0 },
    { forward_context_request_to_handler_e, func_8001793C, D_8001E6B4, 3420, 0 },
    { forward_context_request_to_handler_f, dispatch_entry_or_process_fallback, D_8001E6B4, 3421, 0 },
    { apply_gate_5003_flag_entry, select_square_entry_or_fallback, D_8001E6B4, 3422, 0 },
    { process_entry_with_exit_flag, func_80017B5C, D_8001E6B4, 3423, 0 },
    { forward_context_request_to_handler_g, func_80017C34, D_8001E6B4, 3424, 0 },
    { forward_context_request_to_handler_c_68, select_square_entry_or_alternate, D_8001E6B4, 3425, 0 },
    { func_80017D74, get_shared_entry_buffer, D_8001C33C, 3505, 0 },
    { func_80017E34, invoke_handler_with_code_798, D_8001E6B4, 3426, 0 },
    { return_zero_fn, dispatch_through_table_bbc_4, D_8001E6B4, 0, 0 },
};
