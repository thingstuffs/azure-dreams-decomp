/* Item menu page format and its file-private helper. */
#include "common.h"
#include "shared/item_menu.h"
#include "shared/object_links.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "engine/item.h"
#include "slus.h"
#include "shared/object_flags.h"
/* Marks the objects referenced by the requested entries, starting at index 20, for removal. */
static void remove_item_menu_entry_objects(struct ItemMenuPart **entries, s32 entryCount) {
    ItemMenuPart **entryCursor;
    ItemMenuPart *entry;
    s32 endIndex;
    s32 entryIndex;

    entryIndex = 0x14;
    entryCount += 0x14;
    if (entryIndex < entryCount) {
        endIndex = entryCount;
        entryCursor = entries + 0x14;
        do {
            entry = *entryCursor;
            entryCursor += 1;
            entryIndex += 1;
            flag_optional_object_for_removal(entry->handler);
        } while (entryIndex < endIndex);
    }
}

void release_item_menu_list_object(ObjectNodeHeader *object) {
    ItemMenuTransition *display;

    if (object != 0) {
        display = NODE_BODY(object);
        remove_item_menu_entry_objects(display->rows.as_ptr, display->entry_count);
        release_null_terminated_entries(display->allocations);
        NODE_HEADER(display)->flags |= 0x8000;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
