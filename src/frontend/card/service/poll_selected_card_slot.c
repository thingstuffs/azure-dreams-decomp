#include "common.h"
#include "frontend/card.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/service.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service/event_mode_data.h"
#include "frontend/card/service/operation_state_data.h"
#include "frontend/card/service/selected_channel_data.h"

/*
 * Polls the selected card slot, starts and waits for a detected card event, and sets the channel
 * completion flag on state-three completion. Resets operation state and returns status one for an
 * already marked slot, two for completion, or five for an unknown state.
 */
s32 poll_selected_card_slot(void) {
    s32 status;
    s32 *slot_flag;
    s32 *completion_flag;
    s32 selected_slot;
    u32 state;

    state = card_ui_operation_state;
    status = 0;
    if (state != 0) {
        switch (state) {
        case 1:
            slot_flag = &dev_card_channel_completion_flags[0];
            if (card_selected_channel != 0) {
                slot_flag = &dev_card_channel_completion_flags[1];
            }
            if (*slot_flag != 0) {
                card_ui_operation_state = 0;
                status = 1;
            } else if (((_card_status_80408644(0) & 1) != 0) ||
                       ((_card_status_80408644(1) & 1) != 0)) {
                card_dev_drain_hw_events();
                while (_card_load_80408674(card_selected_channel) == 0) {
                }
                card_ui_event_mode = 0;
                card_ui_operation_state = 3;
            }
            return status;
        case 2:
            break;
        case 3:
            selected_slot = card_selected_channel;
            completion_flag = dev_card_channel_completion_flags;
            if (selected_slot != 0) {
                completion_flag++;
                status = 2;
            } else {
                status = 2;
            }
            {
                s16 flag_value;
                flag_value = 1;
                *completion_flag = flag_value;
            }
            card_ui_operation_state = 0;
            break;
        default:
            status = 5;
            break;
        }
    }
    return status;
}
