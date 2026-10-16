#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"


u8 townAdvanceToNextEnabledEntry(void);                                     /* extern */

/* Set unk_02 to 0xFF before forwarding three values to townAdvanceToNextEnabledEntry. */
void townResetEventSelectionAndAdvance(void) {
    D_8001E950->unk_02 = 0xFF;
    townAdvanceToNextEnabledEntry();
}
