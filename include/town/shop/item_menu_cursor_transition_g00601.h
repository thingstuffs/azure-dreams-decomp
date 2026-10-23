#ifndef TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
#define TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
/* Item menu cursor transition declarations (G00601). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0FD4, CL:town/func_800B10F4. */

#include "common.h"

/* Primitive/color record reached through each row display's +4 data slot. */
typedef struct ItemMenuRowPrimitive {
    s8 red, green, blue;
    u8 pad_03[5];
    s16 x, y;
} ItemMenuRowPrimitive;

typedef struct ItemMenuRowDisplay {
    u8 pad_00[4];
    ItemMenuRowPrimitive *data;
} ItemMenuRowDisplay;

/* Four pointer planes, six slots apart: +8, +20, +38 and +50. Names
 * describe their demonstrated horizontal positions, not the text contents. */
typedef struct ItemMenuRows {
    u8 pad_00[4];
    ItemMenuRowDisplay *cursor;
    ItemMenuRowDisplay *left[6];
    ItemMenuRowDisplay *middle[6];
    ItemMenuRowDisplay *text[6];
    ItemMenuRowDisplay *right[6];
} ItemMenuRows;

typedef struct ItemMenuTransition {
    u8 pad_00[4];
    s32 duration;
    s32 progress;
    u8 pad_0C[0x10];
    s32 end_row;
    s32 start_row;
    u8 pad_24[4];
    s32 entry_count;
    u8 pad_2C[0xAC];
    ItemMenuRows *rows;
} ItemMenuTransition;

void style_item_menu_entry_records(ItemMenuTransition *collection);
void animate_item_menu_cursor_transition(ItemMenuTransition *state);

#endif
