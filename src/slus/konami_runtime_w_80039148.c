#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"


void func_800381A4();
void func_800387D0();

/* Clears the record's counter, advances its index if possible, and selects the next handler. */
void func_80039148(Rec_func_800381D0_arg0 *record) {
    record->unk_20 = 0;
    if (record->unk_22 < (record->unk_25 - 1)) {
        record->unk_22 = (s16) ((u16) record->unk_22 + 1);
        if (record->unk_2E == 1) {
            record->unk_18 = 0;
            record->unk_10 = &func_800381A4;
        }
    } else {
        record->unk_10 = &func_800387D0;
    }
}
