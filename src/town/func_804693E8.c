#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"


u8 advance_to_next_enabled_entry(void);                                     /* extern */

/* Set unk_02 to 0xFF before forwarding three values to advance_to_next_enabled_entry. */
void reset_event_selection_and_advance(void) {
    D_8001E950->unk_02 = 0xFF;
    advance_to_next_enabled_entry();
}
