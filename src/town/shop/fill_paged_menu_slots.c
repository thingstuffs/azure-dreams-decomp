#include "town/shop.h"

/* Fill the alternate storage display's ten icon parts. */
void fill_paged_menu_slots(AlternateStorageOwner *object) {
    AlternateStorageSource *source = object->source;

    fill_ten_paged_output_slots(&object->parts[6], &source->page, source->entries);
}
