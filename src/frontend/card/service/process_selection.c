#include "common.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card/service.h"
extern u8 D_800A0000[];

extern s32 card_ui_operation_state;
extern s32 card_selected_channel;
extern s32 card_ui_event_mode;
extern s32 D_8009E390[];

extern void func_80401578(void);
extern s32 func_80408644(s32 slot_selector);
extern s32 libcard_select_slot(s32 slot_selector);

/* Processes the selection selection_state and clears the selected slot on completion. */
s32 process_selection(void)
{
    s32 selection_state;
    s32 return_code;
    s32 *selected_slot;

    selection_state = card_ui_operation_state;
    return_code = 0;
    if (selection_state != 0) {
        switch (selection_state) {
        case 1:
            func_80401578();
            if ((libcard_select_slot(card_selected_channel) != 0) &&
                ((func_80408644(card_selected_channel != 0) & 4) != 0)) {
                card_ui_event_mode = selection_state;
                card_ui_operation_state = card_ui_operation_state + 1;
                break;
            }
            card_ui_operation_state = 0;
            return_code = 5;
            break;
        case 3:
            selected_slot = (s32 *)D_800A0000 - 1820;
            if (card_selected_channel != 0) {
                selected_slot++;
            }
            return_code = 3;
            *selected_slot = 0;
            card_ui_operation_state = 0;
            break;
        default:
            return_code = 5;
            break;
        }
    }
    return return_code;
}
