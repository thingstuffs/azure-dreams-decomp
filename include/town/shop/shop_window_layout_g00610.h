#ifndef TOWN_SHOP_SHOP_WINDOW_LAYOUT_G00610_H
#define TOWN_SHOP_SHOP_WINDOW_LAYOUT_G00610_H
/* Shop window layout declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3A28, CL:town/func_800B3C30. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/timed_stream.h"

/* Five pointer planes begin at +0x10, +0x24, +0x38, +0x4C and +0x60.
 * The layout routine positions all five rows; the population routine stores
 * each row's lookup result, text handle and item handle through those pointers. */
typedef struct ShopWidgetData {
    s32 color; /* packed colour word: set_shop_slot_colors and set_shop_change_indicator_color write it */
    u8 pad_04[4];
    s16 x;
    s16 y;
} ShopWidgetData;

typedef struct ShopWidget {
    union { s32 word; void *pointer; } value;
    ShopWidgetData *data;
} ShopWidget;

typedef struct ShopWindowWidgets {
    /* 0x00 */ ShopWidget *unk_00;
    /* 0x04 */ ShopWidget *record_widget;
    /* 0x08 */ ShopWidget *cursor;
    /* 0x0C */ ShopWidget *unk_0C;
    /* 0x10 */ ShopWidget *rows[5][5];
    /* 0x74 */ ShopWidget *left_child;
    /* 0x78 */ ShopWidget *right_child;
} ShopWindowWidgets;

/* Shop window state passed by the setup routine to its positioning and row
 * population helpers. Only fields used by those helpers are described here. */
typedef struct ShopWindow {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ s32 selected_entry;
    /* 0x0C */ s32 entry_count;
    /* 0x10 */ s32 page;
    /* 0x14 */ s32 page_limit; /* upper page bound used by update_shop_page_edge_flags */
    /* 0x18 */ s32 price_mode;
    /* 0x1C */ s32 page_edge_flags; /* low two bits mark the page bounds */
    /* 0x20 */ u8 pad_20[4];
    /* 0x24 */ s32 item_address;
    /* 0x28 */ FrameState cursor_record; /* cursor stream initialize_shop_window_layout starts on the cursor widget */
    /* 0x34 */ u8 header_record[0x98];
    /* 0xCC */ ShopWindowWidgets *widgets;
} ShopWindow;

typedef struct S_800B1390_0 {
    s32 *unk_m10;
    u8 pad_m0C[0xC];
} S_800B1390_0;

typedef struct S_800B1390_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
    s32 unk_24;
} S_800B1390_1;

void build_shop_panel_records(u8 *);
void position_shop_row_widgets(ShopWindow *menu);
extern M2C_UNK D_800788E0;
extern FrameNode shop_cursor_template;
extern M2C_UNK D_800D15F4;
extern s32 D_800B0824[];
extern void initialize_shop_parts(void *, void *, void *);

/* Functions defined in this translation unit. */
void initialize_shop_window_layout(ShopWindow *ui);
void initialize_shop_window_state(void *record_data, s32 value_20, s32 value_08, s32 value_0c, s32 value_10, s32 value_14, s32 value_24, s32 value_18);
void setup_shop_window(void *object, s32 setup_value_1, s32 setup_value_2, s32 setup_value_3, s32 setup_value_4, s32 setup_value_5, s32 setup_value_6, s32 setup_value_7);

#endif
