#ifndef TOWN_SYSTEM_H
#define TOWN_SYSTEM_H
/* Prototypes of the functions defined in src/town/system/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_800AD7F8_arg0.h"

struct KeimaState;

/* create_paletted_position_object.c */
void create_paletted_position_object(s32 signed_position, s32 palette_index, struct KeimaState *settings, s32 field_28_value);

/* create_user_data_object.c */
void create_user_data_object(s32 user_data);

/* flag_test_conditions.c */
s32 check_all_flag_test_bits(s16 *flag_ids);

/* flag_test_pair_actions.c */
s32 process_flag_test_record(u32 records, s32 condition_arg, u32 context, s32 record_selector);

/* person_idle_dispatch.c */
void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, void *callback_arg, s32 unused_a, s32 unused_b);
void clear_object_status_and_dispatch_target(void *object, void *target, int value, s16 flags);

/* person_timers.c */
void decrement_object_timer_and_update(Rec_func_80094268_arg0 *object, void *callback_arg_1, void *callback_arg_2);
void func_800C3B7C(Rec_func_80094268_arg0 *object, void *callback_arg_1, void *callback_arg_2);
void decrement_object_timer_and_call_handler(Rec_func_80094268_arg0 *object);
void func_800C3BB8(Rec_func_80094268_arg0 *object);

/* randomize_four_entries_and_reset_state.c */
s32 randomize_four_entries_and_reset_state(void);

/* select_sound_command_from_mode.c */
void select_sound_command_from_mode(void);

/* shop_entry_flags.c */
void toggle_selected_entry_flag(Rec_func_800AD7F8_arg0 *state);
s32 sum_flagged_entry_values(u8 *entry, s32 mode);

/* shop_value_dispatch.c */
void process_lshop_value(void *value);
void process_lshop_value_plus_four(u8 *base_value);

#endif
