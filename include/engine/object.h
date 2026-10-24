#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H
/* Prototypes of the functions defined in src/engine/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "records/Rec_D_80082A38.h"

struct InputRecord;
struct S_80035068_0;
struct S_80035090_0;

/* change_map.c */
void change_map(struct InputRecord *input);

/* clear_resident_bitmap_bit.c */
void clear_resident_bitmap_bit(s32 flag_id);

/* dispatch_town_transition.c */
void dispatch_town_transition(void);

/* entry_runtime_clear_value.c */
void clear_twenty_runtime_records(void);

/* entry_runtime_is_record_handler_changed.c */
s32 test_runtime_handler_or_fallback_status(void *context);

/* entry_runtime_set_record_value_and_buffer.c */
void prepare_script_controller_and_set_cursor(void *controller, s32 reset_value, s32 requested_selector);

/* entry_runtime_store_value_in_shifted_slot_pool.c */
s32 enqueue_runtime_pool_script(void *input_data);

/* entry_set_resident_bitmap_bit.c */
void set_resident_bits_for_matching_key(s16 key);

/* entry_test_resident_bitmap_bit.c */
s32 select_resident_resource_table_value(s32 entry_index);

/* initialize_attached_render_node.c */
void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner);

/* obj_cancel_sw_set.c */
s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
s32 runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback(u8 *first_node, u8 *first_transform, u8 *first_context);

/* runtime_clear_state_and_entry_range.c */
void runtime_clear_state_and_entry_range(void);

/* runtime_clear_value.c */
void runtime_clear_value(s32 *value);

/* runtime_find_unused_pool_slot.c */
void *runtime_find_unused_pool_slot(void);

/* runtime_initialize_state_value.c */
void runtime_initialize_state_value(Rec_D_80081FDC *state, s32 initialValue);

/* runtime_is_record_field_set.c */
s32 runtime_is_record_field_set(void *record_data);

/* runtime_is_record_handler_changed.c */
s32 runtime_is_record_handler_changed(Rec_D_80082A38 *record);

/* runtime_prepend_doubly_linked_node.c */
void runtime_prepend_doubly_linked_node(void *owner, struct S_80035068_0 *node);

/* runtime_render_linked_textured_sprites.c */
s32 runtime_render_linked_textured_sprites(u8 *node_data, u8 *position, u8 *render_state);

/* runtime_set_record_byte_three.c */
void runtime_set_record_byte_three(Rec_D_80082A38 *record, s32 value);

/* runtime_set_record_value_and_buffer.c */
void runtime_set_record_value_and_buffer(void *record, s32 value);

/* runtime_store_value_in_shifted_slot_pool.c */
void runtime_store_value_in_shifted_slot_pool(s32 value);

/* runtime_unlink_doubly_linked_node.c */
void runtime_unlink_doubly_linked_node(struct S_80035090_0 *node);

/* set_resident_bitmap_bit.c */
void set_resident_bitmap_bit(s32 bit_id);

/* test_resident_bitmap_bit.c */
s32 test_resident_bitmap_bit(s32 bit_id);

/* Data declarations. */
extern s32 attached_node_initial_word_14;
extern s32 attached_node_initial_word_18;

#endif
