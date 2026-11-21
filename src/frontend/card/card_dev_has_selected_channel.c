#include "common.h"
#include "frontend/card.h"
#include "frontend/card/service/selected_channel_data.h"

/* Returns whether the selected channel is nonzero. */
s32 card_dev_has_selected_channel(void) {
    return card_selected_channel != 0;
}
