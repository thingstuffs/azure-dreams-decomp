#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/save_slot.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/service.h"

/* Chooses a card-load callback from the selected slot header, table state and nonzero-entry count. */
void select_load_slot_callback(CardDevLoadSlotScreen *screen) {
    s32 idx;

    idx = screen->selection;
    if (card_slot_header_cache[idx].fields.marker != 0) {
        NODE_HEADER(screen)->update_callback = card_dev_enter_load_overwrite_confirmation;
        return;
    }
    if (get_table_entry_by_flag() >= 3) {
        NODE_HEADER(screen)->update_callback = card_dev_enter_saving_progress;
        return;
    }
    if (card_dev_count_cached_slots() != 0) {
        card_dev_enter_overwrite_space_advice(screen);
        return;
    }
    card_dev_enter_card_space_advice(screen);
}
