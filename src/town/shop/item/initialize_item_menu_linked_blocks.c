#include "common.h"
#include "shared/menu_display.h"
#include "town/shop/item.h"
#include "town/shop/floating_number_widget_g00612.h"

typedef struct S_800AFF00_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AFF00_0;   /* arg1 in initialize_item_menu_linked_blocks */



/* Initialize two linked data blocks from templates and set their default fields. */
void initialize_item_menu_linked_blocks(ItemMenuDisplayLinks *state, ItemMenuDisplayBlock *primary, ItemMenuDisplayPosition *secondary) {
    S_800AFF00_0 *primary_words = (S_800AFF00_0 *)primary;
    DisplayPositionWords *secondary_defaults = &display_vector_defaults;
    s32 secondary_head;
    s32 initial_offset = -60;

    primary_words->unk_00 = display_block_defaults.words[0];
    primary_words->unk_04 = display_block_defaults.words[1];
    primary_words->unk_08 = display_block_defaults.words[2];
    secondary_head = display_vector_defaults.unk0;
    primary_words->unk_0C = display_block_defaults.words[3];
    secondary->words.unk0 = secondary_head;
    secondary->words.unk4 = secondary_defaults->unk4;
    secondary->words.unk8 = secondary_defaults->unk8;
    state->display = primary;
    state->position = secondary;
    state->unk_00 = 0;
    state->display->x = initial_offset;
    state->display->y = initial_offset;
    state->display->depth = 0x200;
    state->display->ramp = 0;
    state->position->position.offset_y = 0x30;
    state->display->mode = 4;
}
