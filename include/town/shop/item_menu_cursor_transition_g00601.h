#ifndef TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
#define TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
/* Item menu cursor transition declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_800B0FD4, town/func_800B10F4. */

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
    void (*callback)(struct ItemMenuTransition *state);
    s32 duration;
    s32 progress;
    s16 unk_0C;
    s16 unk_0E;
    struct { s16 low, high; } unk_10;
    struct { s16 low, high; } unk_14;
    s16 unk_18;
    u8 pad_1A[2];
    s32 end_row;
    s32 start_row;
    s32 animation_step;
    s32 entry_count;
    u8 pad_2C[8];
    s32 unk_34;
    s32 entry_data_address; /* +0x38: byte table indexed by dispatch_item_menu_entry_callback */
    s32 unk_3C;
    u8 row_data; /* +0x40: address stored in each row display; complete data extent is unestablished */
    u8 pad_41[0x93];
    void *unk_D4;
    union { ItemMenuRows *as_rows; void *as_ptr; } rows;
} ItemMenuTransition;

void style_item_menu_entry_records(ItemMenuTransition *collection);
void animate_item_menu_cursor_transition(ItemMenuTransition *state);
void tick_item_menu_selection_delay(ItemMenuTransition *state);
/* Selection-delay entry address used by the display callback installer. */

void invoke_item_menu_node_callback(ItemMenuTransition *state);
struct ObjectNodeHeader;

#endif
