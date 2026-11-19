#include "common.h"
#include "shared/item_menu.h"
#include "shared/menu_display.h"

typedef union {
    s32 value;
} StackArg;

/* Initialize the owner's instances from defaults and set their position. */
void initialize_positioned_display_templates(ItemMenuPart *owner, MenuDisplayBlock *display, DisplayPositionWords *vector,
                                            s32 x, StackArg y_arg, StackArg z_arg) {
    s32 y = y_arg.value;
    s32 z = z_arg.value;
    MenuDisplayBlock *block_defaults = &display_block_defaults;
    DisplayPositionWords *vector_defaults = &display_vector_defaults;
    s32 *first_word;

    display->words[0] = block_defaults->words[0];
    first_word = &vector_defaults->unk0;
    display->words[1] = block_defaults->words[1];
    display->words[2] = block_defaults->words[2];
    display->words[3] = block_defaults->words[3];

    vector->unk0 = *first_word;
    vector->unk4 = vector_defaults->unk4;
    vector->unk8 = vector_defaults->unk8;

    owner->position = (ItemMenuPartPosition *)display;
    owner->vector = vector;
    owner->handler = 0;

    owner->position->x = x;
    owner->position->y = y;
    owner->position->depth = z;
    owner->position->mode = 4;
}
