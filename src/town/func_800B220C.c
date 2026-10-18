#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF96C_1 {
    void * unk_00;
} S_800AF96C_1;   /* arg0 in store_item_menu_check_result */

typedef struct S_800AF96C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800AF96C_2;   /* ((S_800AF96C_1 *)arg0)->unk_00 in store_item_menu_check_result */


typedef struct S_800AF96C_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_800AF96C_0;   /* arg0 in store_item_menu_check_result; pointer addresses record offset 0x10 */


s32 place_selected_item_menu_entry(void *);                                /* extern */

/* Store the check result and copy the saved value to the record header on success. */
void store_item_menu_check_result(void *record_data) {
    ((S_800AF96C_2 *)(((S_800AF96C_1 *)record_data)->unk_00))->unk_04 = place_selected_item_menu_entry(record_data);
    if (((S_800AF96C_2 *)(((S_800AF96C_1 *)record_data)->unk_00))->unk_04 != 0) {
        ((S_800AF96C_0 *)((u8 *)record_data - 0x10))->unk_00 = (s32) ((S_800AF96C_0 *)((u8 *)record_data
            - 0x10))->unk_14;
    }
}
