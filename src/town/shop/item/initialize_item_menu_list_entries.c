/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/widget_views.h"
#include "engine/util.h"
#include "slus.h"
#include "town/shop.h"
#include "town/shop/item.h"

typedef struct S_800AECA4_2 {
    u8 pad_00[0xD8];
    void * unk_D8;
} S_800AECA4_2;   /* arg0 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x14];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
} S_800AECA4_3;   /* base in initialize_item_menu_list_entries */

typedef struct S_800AECA4_4 {
    u8 pad_00[0x50];
    void * unk_50;
} S_800AECA4_4;

typedef struct S_800AECA4_5 {
    s32 * unk_00;
    s32 ** unk_04;
} S_800AECA4_5;   /* ((S_800AECA4_2 *)arg0)->unk_D8 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_6;   /* ((S_800AECA4_3 *)base)->unk_38 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_7;   /* ((S_800AECA4_3 *)base)->unk_08 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_8;   /* ((S_800AECA4_3 *)base)->unk_20 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_9;

typedef struct S_800AECA4_10 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_10;   /* ((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00 in initialize_item_menu_list_entries */

   /* ((S_800AECA4_6 *)(((S_800AECA4_3 *)base)->unk_38))->unk_04 in initialize_item_menu_list_entries */

   /* ((S_800AECA4_7 *)(((S_800AECA4_3 *)base)->unk_08))->unk_04 in initialize_item_menu_list_entries */

   /* ((S_800AECA4_8 *)(((S_800AECA4_3 *)base)->unk_20))->unk_04 in initialize_item_menu_list_entries */


   /* ((S_800AECA4_10 *)(((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00))->unk_04 in initialize_item_menu_list_entries */

extern u8 menu_leaf_template_6[12];
extern u8 D_80077EF0[12];
extern u8 D_80077EFC[12];

typedef struct S_800AECA4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
    u8 pad_2C[0xC];
    u8 * unk_38;
    u8 pad_3C[0x9C];
    void * unk_D8;
} S_800AECA4_0;   /* arg0 in initialize_item_menu_list_entries */

typedef struct S_800AECA4_1 {
    u8 pad_00[0x8];
    s32 ** unk_08;
    u8 pad_0C[0x14];
    s32 ** unk_20;
    u8 pad_24[0x14];
    void ** unk_38;
    u8 pad_3C[0x14];
    s32 * unk_50;
} S_800AECA4_1;   /* base in initialize_item_menu_list_entries */

/* Initializes the list display entries and activates the list. */
void initialize_item_menu_list_entries(void *list) {
    s16 row_y;
    s16 entry_y;
    s32 row_slot;
    s32 row_index;

    *((S_800AECA4_5 *)(((S_800AECA4_2 *)list)->unk_D8))->unk_04 = &menu_leaf_template_6;
    row_index = 0;
    *((S_800AECA4_5 *)(((S_800AECA4_2 *)list)->unk_D8))->unk_00 = get_menu_count_template(((S_800AECA4_0 *)list)->unk_28);
    ((SignedWidgetYView *)(((S_800AECA4_10 *)(((S_800AECA4_5 *)(((S_800AECA4_2 *)list)->unk_D8))->unk_00))->unk_04))->unk_0A =
        (s16) ((((S_800AECA4_0 *)list)->unk_28 * 8) + 2);
    if (((S_800AECA4_0 *)list)->unk_28 > 0) {
        u8 *row_data_a = D_80077EF0;
        u8 *row_data_b = D_80077EFC;
        entry_y = 0x82;
        row_y = 0xA;
        do {
            u8 *row_slots_m;
            row_slot = row_index * 4;
            {
                S_800AECA4_3 *row_slots = (S_800AECA4_3 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                ((SignedWidgetYView *)(((S_800AECA4_6 *)(row_slots->unk_38))->unk_04))->unk_0A = row_y;
            }
            {
                row_slots_m = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                *((S_800AECA4_1 *)row_slots_m)->unk_38 = list + 0x40;
            }
            {
                row_slots_m = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                ((SignedWidgetYView *)(((S_800AECA4_7 *)(((S_800AECA4_3 *)row_slots_m)->unk_08))->unk_04))->unk_0A = row_y;
            }
            {
                row_slots_m = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                *((S_800AECA4_1 *)row_slots_m)->unk_08 = row_data_a;
            }
            {
                row_slots_m = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                ((SignedWidgetYView *)(((S_800AECA4_8 *)(((S_800AECA4_3 *)row_slots_m)->unk_20))->unk_04))->unk_0A = row_y;
            }
            {
                row_slots_m = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                *((S_800AECA4_1 *)row_slots_m)->unk_20 = row_data_b;
            }
            row_y += 0x10;
            {
                s32 entry_handle = func_8004DC14(get_item_menu_table_entry(*(((S_800AECA4_0 *)list)->unk_38 + row_index)), 1);
                u8 *row_slots = (u8 *)(row_slot + (s32)((S_800AECA4_0 *)list)->unk_D8);
                *((S_800AECA4_1 *)row_slots)->unk_50 = entry_handle;
            }
            row_index += 1;
            row_slot = row_slot + ((S_800AECA4_0 *)list)->unk_D8;
            ((SignedWidgetYView *)(((S_800AECA4_9 *)(((S_800AECA4_4 *)row_slot)->unk_50))->unk_04))->unk_0A = entry_y;
            entry_y += 0x10;
        } while (row_index < ((S_800AECA4_0 *)list)->unk_28);
    }
    ((S_800AECA4_0 *)list)->unk_04 = 1;
    ((S_800AECA4_0 *)list)->unk_08 = 1;
    animate_item_menu_cursor_transition(list);
}
