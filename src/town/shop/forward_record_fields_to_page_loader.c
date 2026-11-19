#include "town/shop.h"

void forward_record_fields_to_page_loader(ItemMenuPart **outputs, StorageOwner *object) {
    StorageSource *source = object->owner;
    fill_ten_paged_entry_slots(outputs, &source->page, source->entries);
}
