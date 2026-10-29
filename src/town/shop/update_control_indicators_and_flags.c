#include "common.h"
#include "town/shop.h"

typedef struct S_800B4AB0_0 {
    void * unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4C];
    void * unk_5C;
} S_800B4AB0_0;   /* arg0 in update_control_indicators_and_flags */

typedef struct S_800B4AB0_1 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    s32 unk_30;
} S_800B4AB0_1;   /* state in update_control_indicators_and_flags */

typedef struct S_800B4AB0_2 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_800B4AB0_2;   /* ((S_800B4AB0_0 *)arg0)->unk_00 in update_control_indicators_and_flags */

typedef struct S_800B4AB0_3 {
    u8 pad_00[0x98];
    void ** unk_98;
    void ** unk_9C;
} S_800B4AB0_3;   /* ((S_800B4AB0_0 *)arg0)->unk_5C in update_control_indicators_and_flags */


extern u8 item_menu_primary_page_data[];
extern u8 card_selection_display_data[];

/* Update control indicators and flags based on the current value and its limits. */
void update_control_indicators_and_flags(S_800B4AB0_0 *control)
{
    S_800B4AB0_1 *range_state;

    if (((S_800B4AB0_2 *)(control->unk_00))->unk_2C > 0) {
        *((S_800B4AB0_3 *)(control->unk_5C))->unk_98 = item_menu_primary_page_data;
        control->unk_0C = control->unk_0C & -3;
    } else {
        *((S_800B4AB0_3 *)(control->unk_5C))->unk_98 = 0;
        control->unk_0C = control->unk_0C | 2;
    }

    range_state = control->unk_00;
    if (range_state->unk_2C < range_state->unk_30) {
        control->unk_0C = control->unk_0C & -2;
        *((S_800B4AB0_3 *)(control->unk_5C))->unk_9C = card_selection_display_data;
    } else {
        control->unk_0C = control->unk_0C | 1;
        *((S_800B4AB0_3 *)(control->unk_5C))->unk_9C = 0;
    }
}
