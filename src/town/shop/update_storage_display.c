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
extern void forward_source_data_to_component(void *object);
extern void update_control_indicators_and_flags(StorageOwner *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);

void update_storage_display(StorageOwner *object) {
    forward_source_data_to_component(object);
    refresh_storage_page(object);
    update_control_indicators_and_flags(object);
    forward_record_fields_to_page_loader(object->work->page_loader, object);
}
