#include "common.h"
#include "engine/graphics.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/paired_choice.h"


/* Process the embedded records at offsets 4 and 0x10. */
void advance_card_boot_stream_pair(CardChoiceOwner *state) {
    advance_timed_tagged_stream(&state->choice_cursors[0]);
    advance_timed_tagged_stream(&state->choice_cursors[1]);
}
