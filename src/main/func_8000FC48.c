#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"

void card_boot_measure_five_line_message();                      /* extern */
extern u8 D_800280B4[];


/* Sets record fields and processes the selected table entry. */
void card_boot_bind_message_dialog_record(Rec_func_8002290C_arg0 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    record->unk_14 = value_14;
    record->unk_20 = value_20;
    record->unk_08 = entry_index;
    record->unk_0C = value_0c;
    card_boot_measure_five_line_message((entry_index * 0x18) + &D_800280B4[0]);
}
