#include "town/shop.h"
#include "shared/object_flags.h"
#include "engine/item.h"
#include "engine/node.h"
#include "engine/resource.h"
#include "engine/text.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "slus.h"
#include "town.h"
#include "town/person.h"
#include "town/shop/object.h"
#include "town/shop/state.h"
extern u8 shop_cursor_template[];
extern u8 D_80071244[];
extern void func_800B5020(void *work);
extern void forward_source_data_to_component(void *object);
extern void update_control_indicators_and_flags(void *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);
extern s32 display_block_defaults[4];
extern DisplayPositionWords display_vector_defaults;
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern ItemMenuPart *func_800B4C94(ItemMenuPart **parts);

void set_storage_entry_text(StorageEntry *entry, s32 text, s32 style, s16 x, s32 y) {
    void *old_text = entry->text;
    if (old_text != 0) {
        flag_object_for_removal(old_text);
        entry->text = 0;
    }
    entry->position->x = x;
    entry->position->y = y;
    entry->text = alloc_parsed_string(text, style);
    entry->position->mode = 1;
}
