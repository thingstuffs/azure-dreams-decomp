#include "common.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card/service.h"
extern u8 D_800A0000[];

extern s32 card_ui_operation_state;
extern s32 card_selected_channel;
extern s32 card_ui_event_mode;
extern s32 D_8009E390[];

extern void invoke_callback_for_four_global_values(void);
extern s32 func_80408644(s32 slot_index);
extern s32 func_80408674(s32 selected_slot);

/*
 * Polls the selected card slot, starts and waits for a detected card event, and sets the channel
 * completion flag on state-three completion. Resets operation state and returns status one for an
 * already marked slot, two for completion, or five for an unknown state.
 */
s32 advance_processing_selected_slot_sets_completion_flag(void) {
    s32 status;
    u32 *slot_flag;
    s32 *completion_flag;
    s32 selected_slot;
    u32 state;

    state = card_ui_operation_state;
    status = 0;
    if (state != 0) {
        switch (state) {
        case 1:
            slot_flag = &D_8009E390[0];
            if (card_selected_channel != 0) {
                slot_flag = &D_8009E390[1];
            }
            if (*slot_flag != 0) {
                card_ui_operation_state = 0;
                status = 1;
            } else if (((func_80408644(0) & 1) != 0) ||
                       ((func_80408644(1) & 1) != 0)) {
                invoke_callback_for_four_global_values();
                while (func_80408674(card_selected_channel) == 0) {
                }
                card_ui_event_mode = 0;
                card_ui_operation_state = 3;
            }
            return status;
        case 2:
            break;
        case 3:
            selected_slot = card_selected_channel;
            completion_flag = (s32 *)D_800A0000;
            completion_flag = (s32 *)((u8 *)completion_flag - 0x1C70);
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
