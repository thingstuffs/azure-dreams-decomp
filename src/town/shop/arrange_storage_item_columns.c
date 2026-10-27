#include "town/shop.h"
#include "shared/object_flags.h"
extern void flag_object_for_removal(void *object);
extern void *alloc_parsed_string(s32 text, s32 style);
extern void initialize_scaled_entry_cursor(void *state, void *entry, void *cursor);
extern u8 shop_cursor_template[];
extern u8 D_80071244[];
extern void func_800B5020(void *work);
extern void populate_paged_entries_with_brightness(void *page, void *source, s32 value);
extern void forward_source_data_to_component(void *object);
extern void update_control_indicators_and_flags(void *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);
extern s32 display_block_defaults[4];
extern DisplayPositionWords display_vector_defaults;
extern s32 func_800B44F0(StorageMenuObject *object, s32 count);
extern ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts);
extern void func_800B44B0(StorageMenuObject *object, ItemMenuStateNode *owner);
extern void register_node(void *object, void *callback);
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern void release_null_terminated_entries(u16 **entries);
extern s32 func_800B4ED8(StorageMenuObject *object, s32 count);
extern ItemMenuPart *func_800B4C94(ItemMenuPart **parts);
extern void initialize_four_slot_object_owner(StorageMenuObject *object, ItemMenuStateNode *owner);
extern s32 realloc_field_0_buffer(s32 *buffer, s32 resource, s32 count);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 handle, void *vector, s32 count);

void arrange_storage_item_columns(StorageEntry **objects) {
    s32 index = 0;
    do {
        objects[index]->position->x = (index / 5) * 128 + 96;
        objects[index]->position->y = (index % 5) * 16 + 136;
        index++;
    } while (index < 10);
}
