#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save_operation.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
extern s32 D_80010208;

/* Set the state from the object and select an action from the global flag. */
void card_dev_start_next_screen(CardSaveOperationBody *menu) {
    s32 actionId;
    s16 state;

    card_dev_effect_mode = 2;
    card_dev_close_events();
    state = 1;
    if (menu->option_index == 0) {
        state = 3;
    }
    D_80011F48 = state;
    actionId = 4;
    if (D_80010208 != 0) {
        actionId = 5;
    }
    request_scene_dispatch_state_8003D548(actionId);
}
