#include "town/shop/storage_page.h"

void forward_paged_record_data(struct ItemMenuPart **parts, AlternateStorageOwner *object) {
    AlternateStorageSource *source = object->source;
    fill_ten_paged_entry_slots(parts, &source->page, source->entries);
}
