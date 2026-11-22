#include "common.h"
#include "shared/menu_display.h"
#include "frontend/card/menu_default_words.h"
#include "frontend/card.h"

extern s32 D_8002D694[];
extern s32 D_8002D698[];
extern s32 D_8002D69C[];

extern s32 D_8002D6A4[];
extern s32 D_8002D6A8[];

/* Initialize the state with default configuration blocks and fixed main settings. */
void card_dev_init_view_defaults(MenuDisplayNode *state, MenuDisplayBlock *main_config, DisplayPositionWords *aux_config) {
    s32 aux_default;
    main_config->words[0] = menu_primitive_defaults[0];
    aux_default = menu_settings_defaults[0];
    main_config->words[1] = D_8002D694[0];
    main_config->words[2] = D_8002D698[0];
    main_config->words[3] = D_8002D69C[0];
    aux_config->unk0 = aux_default;
    aux_config->unk4 = D_8002D6A4[0];
    aux_config->unk8 = D_8002D6A8[0];
    state->block = main_config;
    state->vector = aux_config;
    state->unk_00 = 0;
    state->block->fields.x = -0xA0;
    state->block->fields.y = -0x48;
    state->block->fields.depth = 0x200;
    state->block->fields.mode = 4;
}
