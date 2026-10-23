#ifndef ENGINE_UTIL_H
#define ENGINE_UTIL_H
/* Prototypes of the functions defined in src/engine/util/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8004B298_a1;
struct S_8004DA24_dst;
struct S_8004DA24_src;
struct S_Src;

/* activate_entries_and_clear_state.c */
void activate_entries_and_clear_state(void);

/* add_byte_pair_and_copy_byte_pair.c */
void add_byte_pair_and_copy_byte_pair(struct S_8004DA24_dst *destination, struct S_8004DA24_src *source);

/* alloc_buffer_array.c */
s32 *alloc_buffer_array(s32 *buffers, s32 buffer_count);

/* alloc_object.c */
void *alloc_object_100(char *text, s32 initial_octave, s32 unused_2, s32 extra_value);
void *func_8004DC14(char *text, s32 initial_octave, s32 alloc_arg2, s32 alloc_arg3);

/* alloc_pointer_pool.c */
void *alloc_pointer_pool(void **pool, s32 record_count);
void *func_80048EE4(void **pool, s32 record_count);

/* bcd_to_int.c */
s32 bcd_to_int(s32 packed_bcd);
s32 func_8003F688(s32 packed_bcd);

/* copy_global_short_triplet.c */
void copy_global_short_triplet(struct S_Src *object);

/* copy_indexed_entry_pair.c */
void copy_indexed_entry_pair(short index, int unused, unsigned short *out_field_8, unsigned short *out_field_a);

/* entry_sort_entries_by_key.c */
s32 reserve_sound_ram_region(s32 size);

/* format_int_space_padded.c */
char *format_int_space_padded(int value, unsigned short width, char *buf);
char *func_8004E5A0(int value, unsigned short width, char *buf);

/* mark_record_if_indirect_value_zero.c */
void mark_record_if_indirect_value_zero(u16 *record_data, struct S_8004B298_a1 *value_ref);

/* realloc_field_buffer.c */
s32 *func_80049004(s32 *buffer_slot, s32 entry_count, s32 clear_words);
s32 *realloc_field_0_buffer(s32 *buffer_slot, s32 entry_count, s32 clear_words);

/* reverse_bytes.c */
void *reverse_bytes(u8 *buf, u16 len);

/* runtime_advance_three_component_interpolation.c */
void runtime_advance_three_component_interpolation(void *record_data);

/* runtime_lookup_byte_by_key.c */
u8 runtime_lookup_byte_by_key(s32 key);

/* set_packed_2bit_flag.c */
void func_8003E188(s32 field_index, s32 flag);
void set_packed_2bit_flag(s32 field_index, s32 flag);

/* sort_entries_by_key.c */
void sort_entries_by_key(void);

/* table_handle_assign_consecutive_byte_data_blocks_items_selected_category_index.c */
void table_handle_assign_consecutive_n_19_byte_data_blocks_items_selected_category_index(void);

/* table_handle_decrements_counter_sets_preceding_halfword_global_flag_bit_remains.c */
void table_handle_decrements_counter_sets_preceding_halfword_global_flag_bit_hex_8000_remains(unsigned short *entry_data, int *counter);

/* uint_to_dec_str.c */
char *func_8004E634(u32 num, char *buf);
char *uint_to_dec_str(u32 num, char *buf);

#endif
