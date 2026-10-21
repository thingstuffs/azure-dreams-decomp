#ifndef ENGINE_ITEM_H
#define ENGINE_ITEM_H
/* Prototypes of the functions defined in src/engine/item/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80042A80_Item;

/* calc_item_value.c */
s32 calc_item_value(u8 *item, s32 use_value1);

/* create_item_label.c */
void *create_item_label(void *init_data);

/* create_item_view_for_entry.c */
void create_item_view_for_entry(int target, int record_addr, int entry_value);
void func_8004B854(int target, int record_addr, int entry_value);

/* decode_item_code.c */
void *decode_glyph_rectangle(void *dest, u8 item_code);
void *func_8004E21C(void *dest, u8 item_code);

/* delete_items_and_reset_state.c */
void delete_items_and_reset_state(void);

/* entry_del_t_item_w_ptr.c */
void remove_monster_items_with_negative_status(void);

/* find_item_data_slot.c */
int find_item_data_slot(int first_value, int second_value);

/* free_item_data_slot.c */
void free_item_data_slot(int first_value, int second_value);
void func_8004A7D8(int first_value, int second_value);

/* generate_random_value.c */
void shuffle_byte_array(u8 *bytes, s32 length);

/* get_item_category_flags.c */
s32 get_item_category_flags(struct S_80042A80_Item *item);

/* get_or_create_item_data.c */
void *get_or_create_item_data(s32 category, s32 item);

/* mark_record_pair_dirty.c */
void mark_record_pair_dirty(void *first_ptr, void *second_ptr);

/* open_view_alternate.c */
void open_view_alternate(void *first_data, void *second_data, void *extra_data);

/* open_view_default.c */
void open_view_default(void *first_data, void *second_data, void *extra_data);

/* open_view_primary.c */
void open_view_primary(s32 context, s32 user_data, s32 item);

/* open_view_secondary.c */
void open_view_secondary(void *first_ptr, void *second_ptr, void *last_ptr);

/* release_counted_entries.c */
void release_counted_entries(u16 **entries, s32 count);

/* release_null_terminated_entries.c */
void func_8004B248(u16 **entries);
void release_null_terminated_entries(u16 **entries);

/* resolve_indexed_value.c */
int resolve_indexed_value(int index);

/* selection_sort_elements.c */
void selection_sort_elements(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *));

/* shuffle_category_item_data.c */
void shuffle_category_item_data(s32 category);

/* shuffle_enabled_item_category_pointers.c */
void shuffle_enabled_item_category_pointers(void);

#endif
