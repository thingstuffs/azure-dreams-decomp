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

void arrange_storage_item_columns(StorageEntry **objects) {
    s32 index = 0;
    do {
        objects[index]->position->x = (index / 5) * 128 + 96;
        objects[index]->position->y = (index % 5) * 16 + 136;
        index++;
    } while (index < 10);
}
