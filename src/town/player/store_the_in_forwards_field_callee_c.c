#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination);                         /* extern */


/* Stores the value in the record and forwards it with unk_10 to apply_a_selected_source_byte_destination_adjusts_sixth_byte. */
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, u8 *destination) {
    record->unk_1C = value;
    apply_a_selected_source_byte_destination_adjusts_sixth_byte((u8 *)value, record->unk_10, destination);
}
