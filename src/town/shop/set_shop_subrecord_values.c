#include "common.h"
#include "m2c_compat.h"

void populate_shop_item_rows();                      /* extern */
void set_shop_change_indicator_color();                      /* extern */

typedef struct S_800B1778_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B1778_0;

/* Set two subrecord values and run their associated update routines. */
void set_shop_subrecord_values(s32 record_address, s32 value_10, s32 value_08) {
    S_800B1778_0 *subrecord;

    subrecord = record_address + 0x20;
    subrecord->unk_08 = value_08;
    set_shop_change_indicator_color(subrecord);
    subrecord->unk_10 = value_10;
    populate_shop_item_rows(subrecord);
}
