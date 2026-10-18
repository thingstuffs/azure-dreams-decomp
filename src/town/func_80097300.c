#include "common.h"
#include "shared/town_handler.h"




typedef struct S_80094A60_0 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_80094A60_0;   /* arg1 in call_the_selected_nonzero_table_callee_80094_a_38 */

/* Passes the selected nonzero table value to store_the_in_forwards_field_10_callee_800949_c_4. */
void call_the_selected_nonzero_table_callee_80094_a_38(s32 *values, S_80094A60_0 *selector, void *ptr2) {
    s32 value = values[selector->unk_16];
    if (value != 0) {
        store_the_in_forwards_field_10_callee_800949_c_4(value, (Rec_D_80082D58 *) selector, ptr2);
    }
}
