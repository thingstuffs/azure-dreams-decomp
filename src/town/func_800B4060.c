#include "common.h"
#include "m2c_compat.h"

void position_shop_row_widgets();                      /* extern */

typedef struct S_800B17C0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17C0_0;

/* Store a value in the embedded record and process the record. */
void store_shop_embedded_value(s32 base_addr, s32 value) {
    S_800B17C0_0 *record;

    record = base_addr + 0x20;
    record->unk_08 = value;
    position_shop_row_widgets(record);
}
