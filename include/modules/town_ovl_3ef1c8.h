#ifndef MODULES_TOWN_OVL_3EF1C8_H
#define MODULES_TOWN_OVL_3EF1C8_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/record_ptrs.h"
#include "shared/town_event_state.h"
#include "shared/town_pointees.h"
#include "shared/town_root.h"

typedef s32 (*SceneHandler3)(s32, s32, s32);
typedef struct S_8001747C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8001747C_0;
typedef struct S_80017824_2 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
} S_80017824_2;
typedef struct S_80017824_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017824_0;
typedef struct S_80017824_1 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_80017824_1;
typedef struct S_800178B4_3 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
    s32 * unk_08;
} S_800178B4_3;
typedef struct S_800178B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800178B4_0;
typedef struct S_800178B4_1 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
} S_800178B4_1;
typedef struct S_800178B4_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_800178B4_2;
extern u8 D_8001A92C;
extern s32 D_8001E2F8;
extern s32 D_8001E634;
extern s32 D_8001E79C;
extern s32 D_8001E9C0;
extern s32 D_8001EB10;
extern s32 D_8001EC04;
extern s32 D_8001A934;
extern s32 scene_override_context;
extern s32 scene_result_fallback;
extern s32 D_8001A93C;
extern s32 D_8001A944;
extern s32 D_8001A94C;
extern s32 D_80020E5C;
extern s32 D_8001A954;
extern s32 D_800211DC;
extern s32 D_8001A95C;
extern s32 scene_response_context;
extern s32 D_8001A964;
extern s32 D_8001A96C;
extern s32 D_8001AC3C;
extern s32 D_8001A974;
extern s32 D_8001B6D0;
extern s32 D_8001B824;
extern s32 D_8001C5FB;
extern s32 D_8001C64E;
extern s32 D_8001A97C;
extern s32 D_8001CDF2;
extern s32 D_8001A984;
extern s32 D_8001F560;
extern s32 D_8001A98C;
extern s32 D_8001F690;
extern s8 D_8001FB7F;
extern s32 D_8001A994;
extern s8 D_8001B7AE;
extern s8 D_8001EDD0;
extern s32 D_8001A99C;
extern s8 D_8001EF6C;
extern s8 D_8001F543;
extern s32 D_8001B208;
extern s32 D_8001A9A4;
extern s32 D_8001A9AC;
extern s32 D_8001CFB4;
extern s32 D_8001A9B4;
extern s32 D_8001A9BC;
extern s32 D_8001D270;
extern s32 D_8001A9C4;
extern s32 D_8001B718;
extern s32 D_8001B81C;
extern s32 D_8001AB4C;
extern s32 D_8001AB54;
extern s32 D_8001AB5C;
extern s16 D_8001A91E;
extern s32 D_8001AB94;
extern s32 D_8001ABE8;
extern s32 D_8001B320;
s32 town_table_contains_first_byte_b(u8);
s32 func_8001A510(s32 code);
void func_8001A418(s32 code);
void func_8001A490(s32 code);
s32 func_80016164(s32 first_value, s32 second_value);
s32 func_8001A7F8(void);
s32 func_80019A04(void *table, s32 key, s32 context);
s32 *func_80019ABC(void *table, void *state, s32 key, s32 context);
s32 func_80019928();
s32 func_80019880(void);
s32 func_800196F4();
s32 is_four_arg_result_valid();
s32 func_80019778();
void apply_four_values_and_refresh();
void func_80018F74();
s32 func_8001979C();
void func_800187AC(void);
s32 apply_signed_value_to_indexed_entry(s32 object, s32 index);
s32 func_80019814(void *object, s32 index);
s32 func_8001A220(s32, s32, s32);
s32 check_any_entry_matches_predicate(void);
s32 lookup_variant_with_special_overrides(s32 requiredFlag, s32 completionFlag);
s32 *select_state_result_with_lookup_overrides(s32 first_value, s32 second_value, s32 unused_context);
s32 select_table_result_with_override(s32 context, s32 check_value, s32 selector);
void call_clear_script_flag_bit(s32 context, s32 entry_index);
s32 query_state_with_selector_10(s32 context, s32 check_value, s32 selector);
void forward_context_value_to_handler_a(s32 input_a, s32 input_b);
s32 select_scene_result_with_overrides(s32 context, s32 check_value, s32 selector);
void forward_context_value_to_handler_b(s32 first_value, s32 second_value);
void *select_lookup_with_progress_threshold(s32 selector, s32 check_value, s32 lookup_value);
void forward_context_value_to_handler_c(s32 context, s32 value);
s32 select_lookup_with_count_threshold(s32 object, s32 check_value, s32 selection);
void select_based_parameters(s32 context, s32 entry_index);
s32 run_preliminary_callback_count_ten(s32 context, s32 check_value, s32 selector);
s32 update_scene_action_flags(s32 context, s32 check_value, s32 selector);
s32 dispatch_code_7_a_0_by_status(void);
void invoke_handler_with_code_7_a_0(void);
s32 check_interaction_13_type_3(void);
s32 select_interaction_result_with_refresh(s32 input, s32 check_value, s32 context);
void invoke_match_callback_or_lookup(void);
void invoke_handler_with_code_7_a_1(void);
void invoke_alternate_handler_with_code_7_a_1(void);
#include "town/scene/record_services.h"
void invoke_handler_with_code_47_d(void);
s32 *select_response_by_selector_and_flags(s32 context, s32 check_value, s32 selector);
s32 wait_for_dialogue_then_close(void *object, s32 entry_index);
s32 select_dialogue_with_799_override(s32 speaker, s32 interaction, s32 dialogue_id);
s32 dispatch_by_state_code_0x798(s32 handler_arg_a, s32 handler_arg_b);
s32 select_lookup_or_threshold_fallback(s32 value, s32 check_value, s32 lookup_value);
s32 dispatch_menu_pair_by_798_state(s32 slot_index, s32 slot_value);
s32 select_object_response_by_status(void *object, s32 check_mode, s32 context);
s32 dispatch_entry_by_798_state(s32 handler_arg_a, s32 handler_arg_b);
s8 *get_progress_byte_pointer(void);
s32 select_handler_by_state_code_0x798(s32 primaryInput, s32 secondaryInput);
s32 lookup_entry_with_default_fallback(s32 value, s32 check_value, s32 lookup_value);
s32 func_80017100(s32 value, s32 check_value, s32 lookup_value);
s32 dispatch_by_state_code_0x799(s32 slot_index, s32 slot_value);
s32 select_one_time_interaction_response(void *object, s32 check_value, s32 selection);
s32 dispatch_entry_by_799_flag(s32 context, s32 entryIndex);
#include "town/scene/entry_requests.h"
s32 dispatch_entry_and_set_11_fb_when_flagged(s32 context, s32 entry_index);
s32 select_event_fallback_event_handler(s32 object, s32 request, s32 context);
s32 dispatch_entry_by_798_and_799_flags(s32 context, s32 entry_index);
s32 lookup_entry_with_fallback_b(s32 context, s32 check_value, s32 selector);
s32 func_800175B4(s32 context, s32 check_value, s32 selector);
s32 select_mode_nine_lookup(s32 input, s32 context, s32 mode);
s32 check_ready_or_run_followup(void);
s32 func_80017724(void);
s32 lookup_entry_with_fallback_c(s32 context, s32 check_value, s32 selector);
s32 func_80017758(s32 context, s32 check_value, s32 selector);
void mark_progress_state_ready(void);
s32 initialize_indexed_entry_on_first_479(S_80017824_0 *obj, s32 index);
s32 start_interaction_on_code_0x479(S_800178B4_0 *menu, s32 index);
s32 lookup_entry_with_fallback_after_refresh(s32 input, s32 check_value, s32 context);
s32 func_8001799C(s32 input, s32 check_value, s32 context);
void forward_context_value_to_handler_d(s32 first_arg, s32 second_arg);
s32 lookup_entry_with_fallback_d(s32 context, s32 check_value, s32 selector);
s32 func_80017A70(s32 context, s32 check_value, s32 selector);
void forward_context_value_to_handler_e(s32 first_input, s32 second_input);
s32 lookup_entry_with_fallback_e(s32 context, s32 check_value, s32 selector);
s32 func_80017B40(s32 context, s32 check_value, s32 selector);
void clear_progress_and_dispatch_code_12_cb(s32 handler_id, s32 handler_arg);
void invoke_handler_with_code_780(void);
void invoke_alternate_handler_with_code_780(void);
void invoke_status_handler_with_code_780(void);
void invoke_status_handler_with_code_1470(void);
void invoke_handler_with_code_1470(void);
void invoke_alternate_handler_with_code_79_e(void);
void invoke_handler_with_code_79_e(void);
void select_scene_choice_by_mode(void);
void invoke_handler_with_code_798(void);
void invoke_handler_with_code_799(void);
void invoke_handler_with_code_11_fb(void);
void invoke_alternate_handler_with_code_11_fb(void);
#include "town/scene/fixed_position.h"
s32 start_callback_with_fixed_parameters(void);
/* Incomplete inherited argument-list evidence; retain the caller register passthrough. */
s32 check_table_result_below_minus_47();

#endif
