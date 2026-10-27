#ifndef ENGINE_ITEM_H
#define ENGINE_ITEM_H
/* Prototypes of the functions defined in src/engine/item/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct DungeonItemEntry;

s32 select_item_data(struct DungeonItemEntry *item, s32 *out_mode);

/* Twenty-byte category record. Category 19 uses text_04 as the species name
 * and text_08 as its description; other categories select their text by state.
 * data is a runtime item-data slot in categories that allocate item state.
 * The last two halfwords are selected by calc_item_value and its callback. */
typedef struct ItemRecord {
    u16 flags;
    s16 unk_02;
    const char *text_04;
    const char *text_08;
    void *data;
    u16 value0;
    u16 value1;
} ItemRecord;

/* Record format (+0) selects 20- versus 12-byte entries. Name format (+0x10)
 * independently selects the modifier/status text emitted by format_item_name.
 * Unknown trailing bytes remain live/unknown, rather than claimed padding. */
typedef struct ItemCategory {
    u8 record_format;
    u8 flags;
    u8 count;
    u8 multiplier_index;
    const char *label;
    s32 (*callback)(s32, void *, void *, void *);
    void *records;
    u8 name_format;
    u8 unk_11[3];
} ItemCategory;

extern ItemCategory itemCategoryTable[];
/* Element zero holds the category-19 records. [4] preserves the resident
 * pointer object's non-small-data addressing; it is not a species count. */
extern ItemRecord *monster_species_table[4];

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
s32 get_item_category_flags(struct DungeonItemEntry *item);

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
