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
#include "town/shop/shop_window_layout_g00610.h"
extern u8 D_80071244[];

void initialize_storage_cursor(StorageOwner *object) {
    initialize_scaled_entry_cursor(&object->cursor, &shop_cursor_template, (int *)&object->parts[4]->handler);
    object->parts[5]->handler = D_80071244;
}
