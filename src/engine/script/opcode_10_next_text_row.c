#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"
#include "engine/message.h"
#include "engine/script.h"

/* Clears the record's counter, advances its index if possible, and selects the next handler. */
void handle_vm_opcode_10(Rec_func_800381D0_arg0 *record) {
    record->unk_20 = 0;
    if (record->unk_22 < (record->unk_25 - 1)) {
        record->unk_22 = (s16) ((u16) record->unk_22 + 1);
        if (record->unk_2E == 1) {
            record->unk_18 = 0;
            record->unk_10 = &decrement_countdown_and_switch;
        }
    } else {
        record->unk_10 = &scroll_message_rows;
    }
}
