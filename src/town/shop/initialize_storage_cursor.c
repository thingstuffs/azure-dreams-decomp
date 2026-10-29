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
extern void update_control_indicators_and_flags(void *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);
extern s32 display_block_defaults[4];
extern DisplayPositionWords display_vector_defaults;
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern ItemMenuPart *func_800B4C94(ItemMenuPart **parts);

void initialize_storage_cursor(StorageOwner *object) {
    initialize_scaled_entry_cursor(object->cursor, shop_cursor_template, object->work->cursor);
    *object->work->target = D_80071244;
}
