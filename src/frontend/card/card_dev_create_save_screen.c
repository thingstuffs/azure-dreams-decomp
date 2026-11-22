#include "shared/object_node.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_imports.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct CardSaveScreenState {
    ObjectNodeHeader node;
    CardSaveOperationBody body;
} CardSaveScreenState;

extern u8 D_8040C628[0x1C];

/* Creates and initializes state and installs its update callback. */
CardSaveScreenState *card_dev_create_save_screen(ObjectNodeHeader *request) {
    CardSaveScreenState *state;

    state = func_8003C714(0, D_8040C628, 0x1C);
    {
        CardSaveOperationBody *body = &state->body;
        card_dev_run_init_hook(body, request);
        run_slot_operation_code_five();
        card_dev_cache_slot_summary();
        body->slot_mode = 1;
        body->background = init_card_background_object(&state->node, &body->slot_mode);
        body->options = init_card_options_object(&state->node);
        body->information = init_card_info_object(&state->node, body->entry_index);
    }
    state->body.window_index = 0;
    state->node.update_callback = card_devkit_build_save_slot_windows;
    return state;
}
