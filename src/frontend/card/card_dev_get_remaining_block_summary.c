#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/service/selected_channel_data.h"

/* Selects a block summary using the selected channel. */
s32 card_dev_get_remaining_block_summary(void) {
    s32 *entry = dev_card_remaining_8k_blocks;

    if (card_selected_channel != 0) {
        entry++;
    }
    return *entry;
}
