#include "common.h"
#include "m2c_compat.h"
#include "shared/types3a_types.h"

void position_shop_row_widgets();                      /* extern */


/* Store a value in the embedded record and process the record. */
void store_shop_embedded_value(s32 base_addr, s32 value) {
    EffectStateWordView *record;

    record = base_addr + 0x20;
    record->unk_08 = value;
    position_shop_row_widgets(record);
}
