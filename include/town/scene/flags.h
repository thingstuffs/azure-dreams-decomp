#ifndef TOWN_SCENE_FLAGS_H
#define TOWN_SCENE_FLAGS_H

#include "common.h"


/* clear_referenced_object_active_flag.c */
void clear_referenced_object_active_flag(void);


/* set_referenced_object_active_flag.c */
void set_referenced_object_active_flag(void);


/* clear_indexed_flag_bit_unless_index_one.c */
void clear_indexed_flag_bit_unless_index_one(s32 bit_index);


/* update_flag_test_target.c */
void update_flag_test_target(s16 sourceId, s16 targetId);


/* set_indexed_flag_bit.c */
void set_indexed_flag_bit(s32 flag_id);

/* Callback entry points. */
void clear_global_entry_flag(void);
void fade_panel_after_linked_flag(void *effect);

void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void set_current_entry_script_flag(void);

void clear_indexed_flag_unless_identifier(s32 flag_id);
s32 *get_flag_test_table_address(void);
void set_flag_test_indexed_bit(s32 bit_index);

struct S_80016818_0;
s32 run_flag_test_callbacks(struct S_80016818_0 *context);

void dispatch_flag_test_state(void);

#include "records/Rec_func_800165F4_arg0.h"
void apply_record_value_for_either_flag(Rec_func_800165F4_arg0 *object, s32 context);
void dispatch_entry_for_active_flags(void *context, s32 entry_index);
u8 *dispatch_or_override_for_flag_1390(s32 dispatch_arg, s32 unused, s32 dispatch_option);
void post_code_107_if_entry_bit_0(s32 row, s32 column);
s32 resolve_entry_flag(void *entry_table, void *context, s32 entry_key);
u8 *select_context_data_with_flag_override(void *context, s32 unused, s32 selector);
s32 set_record_flag_on_query_failure(void *record_field, s32 query_value);
s32 test_indexed_flag_bit(s32 bit);
s32 update_scene_flag_5_c_4(void);

#endif
