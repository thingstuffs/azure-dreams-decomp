#include "common.h"

void flag_optional_object_for_removal(void *object);

/*
 * Flags referenced objects for removal across the requested number of entry-table slots, starting
 * at slot 20.
 */
void send_item_menu_page_entries_to_formatter(s32 entryTableAddress, s32 entryCount) {
    s32 **entryCursor;
    s32 *entry;
    s32 endIndex;
    s32 entryIndex;

    entryIndex = 0x14;
    entryCount += 0x14;
    if (entryIndex < entryCount) {
        endIndex = entryCount;
        entryCursor = entryTableAddress + 0x50;
        do {
            entry = *entryCursor;
            entryCursor += 1;
            entryIndex += 1;
            flag_optional_object_for_removal(*entry);
        } while (entryIndex < endIndex);
    }
}
