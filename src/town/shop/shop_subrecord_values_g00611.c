/* Shop subrecord values (G00611). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3FDC. */
#include "town/shop/shop_subrecord_values_g00611.h"
#include "town/shop.h"

/* Set the decrease or increase indicator color when the current and target values differ. */
void set_shop_change_indicator_color(S_800B173C_0 *record, s32 target_value) {
    s32 indicators_address;
    s32 current_value;
    void **indicator_entry;

    current_value = record->unk_10;
    if (current_value != target_value) {
        indicators_address = record->unk_CC;
        if (current_value >= target_value) {
            indicator_entry = indicators_address + 0x74;
        } else {
            indicator_entry = indicators_address + 0x78;
        }
        *((S_800B173C_1 *)(*indicator_entry))->unk_04 = 0xE0E0E0;
    }
}

/* Set two subrecord values and run their associated update routines. */
void set_shop_subrecord_values(s32 record_address, s32 value_10, s32 value_08) {
    S_800B1778_0 *subrecord;

    subrecord = record_address + 0x20;
    subrecord->unk_08 = value_08;
    set_shop_change_indicator_color((S_800B173C_0 *)subrecord, value_10);
    subrecord->unk_10 = value_10;
    populate_shop_item_rows((struct S_800B0FD4_0 *)(subrecord));
}
