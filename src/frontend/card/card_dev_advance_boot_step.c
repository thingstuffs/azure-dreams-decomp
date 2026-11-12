#include "common.h"
#include "frontend/card/event_callbacks.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service/event_mode_data.h"
#include "frontend/card/service/operation_state_data.h"
#include "main/data.h"

/* Boot step 2: run the loader and either request retry code 5 or bump the attempt counter. */
s32 card_dev_advance_boot_step(void) {
    s32 result;

    result = 0;

    if (card_ui_operation_state == 2) {
        invoke_callback_for_four_global_values();
        if (_card_load_80408674(card_selected_channel) == 0) {
            D_804094E8_2[0] = 0;
            result = 5;
        } else {
            card_ui_event_mode = 0;
            D_804094E8_3[0] = D_804094E8_4[0] + 1;
        }
    }
    return result;
}
