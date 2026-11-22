#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card/menu_default_words.h"
#include "frontend/card.h"

extern s32 D_8002D694[];
extern s32 D_8002D698[];
extern s32 D_8002D69C[];

extern s32 D_8002D6A4[];
extern s32 D_8002D6A8[];

/* Initialize an entry from defaults and set its row position. */
void card_dev_init_row_view(CardDevMenuEntry *entry, MenuDisplayBlock *placement, s32 *settings, s32 row_index) {
    s32 settings_header;

    placement->words[0] = menu_primitive_defaults[0];
    settings_header = menu_settings_defaults[0];
    placement->words[1] = D_8002D694[0];
    placement->words[2] = D_8002D698[0];
    placement->words[3] = D_8002D69C[0];
    settings[0] = settings_header;
    settings[1] = D_8002D6A4[0];
    settings[2] = D_8002D6A8[0];
    entry->display.block = placement;
    entry->settings = settings;
    entry->display.payload.word = 0;
    entry->display.block->fields.x = -0xA0;
    entry->display.block->fields.y = (s16) ((row_index * 0x18) - 0x78);
    entry->display.block->fields.depth = 0x200;
    entry->display.block->fields.mode = 4;
}
