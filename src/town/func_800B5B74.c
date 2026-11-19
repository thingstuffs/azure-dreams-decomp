#include "town/shop/storage_menu.h"
#include "town.h"

void func_800B39E4(void *);

/* Refresh the alternate storage menu's ten text parts. */
void populate_record_page_entries(AlternateStorageOwner *record) {
    AlternateStorageSource *source;

    func_800B39E4(record->parts);
    source = record->source;
    populate_paged_entries_with_brightness(&record->parts[16], &source->page, source->entries);
}
