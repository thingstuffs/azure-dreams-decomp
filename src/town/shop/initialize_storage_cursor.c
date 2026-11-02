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

void initialize_storage_cursor(StorageOwner *object) {
    initialize_scaled_entry_cursor(object->cursor, shop_cursor_template, object->work->cursor);
    *object->work->target = D_80071244;
}
