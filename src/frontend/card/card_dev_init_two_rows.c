#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"


/* Process the two embedded records at offsets 4 and 0x10. */
void card_dev_advance_slot_stream_pair(CardDevSlotMenu *panel) {
    advance_timed_tagged_stream_8004DCCC(&panel->cursors[0]);
    advance_timed_tagged_stream_8004DCCC(&panel->cursors[1]);
}
