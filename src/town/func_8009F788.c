#include "modules/town_town_windows.h"

/* Builds the entry list and processes each entry's items at its coordinates. */
void townBuildEntryListAndProcessItems(void) {
    s32 setup_a[2];
    s32 setup_b[2];
    s32 *item_cursor;
    s32 coord_x;
    s32 coord_y;
    void **entry_cursor;
    func_8009F788_S_8009CEE8_0 *entry;
    u16 *base;

    base = D_80082D08;
    townComputeFourPointCoordinateBounds(base, setup_a, setup_b);
    townCollectOverlappingRectangles(setup_a, setup_b, D_80100900, D_801007F8);
    entry_cursor = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
        do {
            entry = *entry_cursor;
            item_cursor = entry->unk_0C;
            if (item_cursor != NULL) {
                coord_x = entry->unk_00;
                coord_y = entry->unk_02;
                while (*item_cursor != 0) {
                    townProcessEligibleEntries(*item_cursor, base, (s16)coord_x, (s16)coord_y);
                    item_cursor++;
                }
            }
            entry_cursor = (void **)((s8 *)((void **)((s8 *)entry_cursor + 4)));
        } while (*entry_cursor != NULL);
    }
}
