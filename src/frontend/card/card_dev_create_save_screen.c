#include "shared/object_node.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/server_imports.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct CardSaveScreenState {
    s8 pad00[0x10];
    void (*unk10)(void);
    s8 pad14[0x0C];
    void *background;
    s8 pad24[0x14];
    s32 unk38;
    void *information;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s8 pad4C[0x1C];
    s32 unk68;
} CardSaveScreenState;

extern void run_slot_operation_code_five(void);
extern u8 D_8040C628[0x1C];

/* Creates and initializes state and installs its update callback. */
CardSaveScreenState *card_dev_create_save_screen(s32 init_value) {
    CardSaveScreenState *state;

    state = func_8003C714(0, D_8040C628, 0x1C);
    {
        u8 *body = NODE_BODY(state);
        card_dev_run_init_hook(body, init_value);
        run_slot_operation_code_five();
        card_dev_cache_slot_summary();
        state->unk68 = 1;
        state->background = init_card_background_object(NODE_HEADER(body), &state->unk68);
        state->unk38 = init_card_options_object(state);
        state->information = init_card_info_object(NODE_HEADER(body), state->unk48);
    }
    state->unk44 = 0;
    state->unk10 = card_devkit_build_save_slot_windows;
    return state;
}
