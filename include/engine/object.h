#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H
/* Prototypes of the functions defined in src/engine/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
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
void clear_object_pool_records(void);

/* entry_runtime_is_record_handler_changed.c */
s32 is_script_or_map_change_pending(void *context);

/* entry_runtime_set_record_value_and_buffer.c */
void reset_script_message_window(void *controller, s32 reset_value, s32 requested_selector);

/* entry_runtime_store_value_in_shifted_slot_pool.c */
s32 queue_pool_service_script(void *input_data);

/* entry_set_resident_bitmap_bit.c */
void set_resident_bits_for_matching_key(s16 key);

/* entry_test_resident_bitmap_bit.c */
s32 select_resident_resource_table_value(s32 entry_index);

/* initialize_attached_render_node.c */
void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner);

/* obj_cancel_sw_set.c */
s32 obj_disp23_cancel_sw_set(s32 cancel_switch);
s32 draw_linked_sprite_nodes(u8 *first_node, u8 *first_transform, SpriteFrameState *first_context);

/* clear_script_pending_values.c */
void clear_script_pending_values(void);

/* clear_word.c */
void clear_word(s32 *value);

/* find_free_pool_record.c */
void *find_free_pool_record(void);

/* init_unit_scale_record.c */
void init_unit_scale_record(Rec_D_80081FDC *state, s32 initialValue);

/* is_node_registered.c */
s32 is_node_registered(void *record_data);

/* has_active_script_handler.c */
s32 has_active_script_handler(Rec_D_80082A38 *record);

/* entry_runtime_prepend_doubly_linked_node.c: links the self-reference at body +0x54. */
void prepend_embedded_object_node(void *owner, void *object_data);

/* prepend_owner_list_node.c */
void prepend_owner_list_node(void *owner, void *node_data);

/* draw_sprites_with_dimmed_copies.c */
s32 draw_sprites_with_dimmed_copies(u8 *node_data, ObjectPosition *position, u8 *render_state);

/* runtime_set_record_byte_three.c */
void runtime_set_record_byte_three(Rec_D_80082A38 *record, s32 value);

/* set_script_text_pointer.c */
void set_script_text_pointer(void *record, s32 value);

/* push_script_slot_value.c */
void push_script_slot_value(s32 value);

/* unlink_owner_list_node.c */
void unlink_owner_list_node(void *node_data);

/* set_resident_bitmap_bit.c */
void set_resident_bitmap_bit(s32 bit_id);

/* test_resident_bitmap_bit.c */
s32 test_resident_bitmap_bit(s32 bit_id);

/* Data declarations. */
extern s32 attached_node_initial_word_14;
extern s32 attached_node_initial_word_18;

#endif
