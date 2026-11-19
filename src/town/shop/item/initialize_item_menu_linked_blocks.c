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


   /* arg2 in initialize_item_menu_linked_blocks */


typedef struct S_800AFF00_4 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_800AFF00_4;   /* arg0 in initialize_item_menu_linked_blocks */

typedef struct S_800AFF00_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AFF00_5;   /* dst in initialize_item_menu_linked_blocks */

typedef struct S_800AFF00_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1];
    u8 unk_0F;
} S_800AFF00_6;   /* ((S_800AFF00_4 *)arg0)->unk_04 in initialize_item_menu_linked_blocks */

typedef struct S_800AFF00_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AFF00_7;   /* ((S_800AFF00_4 *)arg0)->unk_08 in initialize_item_menu_linked_blocks */

/* Initialize two linked data blocks from templates and set their default fields. */
void initialize_item_menu_linked_blocks(ItemMenuDisplayLinks *state, S_800AFF00_0 *primary, DisplayPositionWords *secondary) {
    MenuDisplayBlock *primary_defaults = &display_block_defaults;
    DisplayPositionWords *secondary_defaults = &display_vector_defaults;
    s32 secondary_head;
    s32 initial_offset = -60;

    primary->unk_00 = display_block_defaults.words[0];
    primary->unk_04 = primary_defaults->words[1];
    primary->unk_08 = primary_defaults->words[2];
    secondary_head = display_vector_defaults.unk0;
    primary->unk_0C = primary_defaults->words[3];
    secondary->unk0 = secondary_head;
    secondary->unk4 = secondary_defaults->unk4;
    secondary->unk8 = secondary_defaults->unk8;
    state->display = (ItemMenuDisplayBlock *)primary;
    state->position = secondary;
    state->unk_00 = 0;
    state->display->x = initial_offset;
    state->display->y = initial_offset;
    state->display->depth = 0x200;
    state->display->ramp = 0;
    ((S_800AFF00_7 *)state->position)->unk_08 = 0x30;
    state->display->mode = 4;
}
