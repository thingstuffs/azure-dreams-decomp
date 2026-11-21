#include "common.h"
#include "frontend/card/server_menu.h"
#include "frontend/card/server_imports.h"

/* One 12-byte entry of a card-grid row in the devkit server. */
typedef struct CardDevRowEntry {
    u8 bytes[12];
} CardDevRowEntry;

/* Applies mode 1 to the whole row, then mode 0 to `count` entries starting at `first`. */
void card_dev_mark_row_entry_range(CardDevRowEntry *entries, s32 first, s32 count)
{
    s32 i;

    set_card_grid_row_mode_80051DE4(entries, 1);
    entries += first;
    for (i = 0; i < count; i++) {
        set_card_grid_entry_mode_800514A8(entries, 0);
        entries++;
    }
}
