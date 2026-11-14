#ifndef ENGINE_UTIL_H
#define ENGINE_UTIL_H
/* Prototypes of the functions defined in src/engine/util/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "engine/camera/interpolation.h"

struct S_8004B298_a1;
struct S_8004DA24_dst;
struct S_8004DA24_src;
struct S_Src;

/* reset_sequence_track_state.c */
void reset_sequence_track_state(void);

/* add_byte_pair_and_copy_byte_pair.c */
void add_byte_pair_and_copy_byte_pair(struct S_8004DA24_dst *destination, struct S_8004DA24_src *source);

/* alloc_buffer_array.c */
s32 *alloc_buffer_array(s32 *buffers, s32 buffer_count);

/* alloc_object.c */
void *create_label_glyph_entries(char *text, s32 glyph_style);
void *func_8004DC14(char *text, s32 glyph_style);

/* alloc_pointer_pool.c */
void *alloc_pointer_pool(void **pool, s32 record_count);
void *func_80048EE4(void **pool, s32 record_count);

/* bcd_to_int.c */
s32 bcd_to_int(s32 packed_bcd);
s32 func_8003F688(s32 packed_bcd);

/* copy_view_source_position.c */
void copy_view_source_position(struct S_Src *object);

/* get_sequence_slot_gains.c */
void get_sequence_slot_gains(short index, int unused, unsigned short *out_field_8, unsigned short *out_field_a);

/* entry_sort_entries_by_key.c */
s32 reserve_sound_ram_region(s32 size);

/* format_int_space_padded.c */
char *format_int_space_padded(int value, unsigned short width, char *buf);
char *func_8004E5A0(int value, unsigned short width, char *buf);

/* flag_removal_when_value_zero.c */
void flag_removal_when_value_zero(u16 *record_data, struct S_8004B298_a1 *value_ref);

/* realloc_field_buffer.c */
s32 *func_80049004(s32 *buffer_slot, s32 entry_count, s32 clear_words);
s32 *rebuild_pointer_pool(s32 *buffer_slot, s32 entry_count, s32 clear_words);

/* reverse_bytes.c */
void *reverse_bytes(u8 *buf, u16 len);

/* advance_camera_interpolation.c */
void advance_camera_interpolation(CameraInterpolationBody *record_data);

/* lookup_resident_byte_by_key.c */
s32 lookup_resident_byte_by_key(s32 key);

/* set_packed_2bit_flag.c */
void func_8003E188(s32 field_index, s32 flag);
void set_packed_2bit_flag(s32 field_index, s32 flag);

/* sort_sound_ram_blocks.c */
void sort_sound_ram_blocks(void);

/* table_handle_assign_consecutive_byte_data_blocks_items_selected_category_index.c */
void assign_item_category_data_blocks(void);

/* table_handle_decrements_counter_sets_preceding_halfword_global_flag_bit_remains.c */
void decrement_and_flag_removal_if_nonzero(unsigned short *entry_data, int *counter);

/* uint_to_dec_str.c */
char *func_8004E634(u32 num, char *buf);
char *uint_to_dec_str(u32 num, char *buf);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/entity.h"
s32 take_status_slot_value(ActorRecord *slots, s8 type);
s32 func_80042518(ActorRecord *slots, s8 type);

#endif
