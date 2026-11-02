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
extern void func_800B5020(void *work);

void refresh_storage_page(StoragePageOwner *object) {
    func_800B5020(object->work);
    populate_paged_entries_with_brightness(object->work->page, object->source->page, object->source->value);
}
