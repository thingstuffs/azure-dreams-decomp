#ifndef TOWN_MENU_ALTERNATE_PAGE_RECORDS_G00619_H
#define TOWN_MENU_ALTERNATE_PAGE_RECORDS_G00619_H
/* inferred-strong alternate_page_records_g00619; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80035C0C, CL:town/func_800B5978, CL:town/func_800B5B74. */

/* Update alternate menu page bounds. */
#include "common.h"
#include "town/shop/storage_menu.h"
#include "slus/card_selection_display_data.h"
#include "slus/item_menu_primary_page_data.h"

void forward_paged_record_data(ItemMenuPart **parts, AlternateStorageOwner *object);
/* extern */
void fill_paged_menu_slots(AlternateStorageOwner *);
void populate_record_page_entries(AlternateStorageOwner *);

/* Functions defined in this translation unit. */
void update_alternate_menu_page_bounds(AlternateStorageOwner *obj);
void update_paged_menu_record(AlternateStorageOwner *record);

#endif
