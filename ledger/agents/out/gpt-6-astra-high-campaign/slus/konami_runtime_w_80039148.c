#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"



extern M2C_UNK func_800381A4;
extern M2C_UNK func_800387D0;

/* Clears the record's counter, advances its index if possible, and selects the next handler. */
void func_80039148(Rec_func_800381D0_arg0 *record) {
    M2C_UNK *next_handler;

    record->unk_20 = 0;
    if (record->unk_22 < (record->unk_25 - 1)) {
        record->unk_22 = (s16) ((u16) record->unk_22 + 1);
        if (record->unk_2E == 1) {
            next_handler = &func_800381A4;
            record->unk_18 = 0;
            goto block_4;
        }
    } else {
        next_handler = &func_800387D0;
block_4:
        record->unk_10 = next_handler;
    }
}
