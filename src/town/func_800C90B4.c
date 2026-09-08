#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800C641C(Rec_func_80094268_arg0 *);                            /* extern */


/* Decrement the record's countdown and run its follow-up calls when it expires. */
void func_800C6814(Rec_func_80094268_arg0 *record, M2C_UNK forward_arg1, M2C_UNK forward_arg2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C641C(record);
        func_800C4174(record, forward_arg1, forward_arg2);
    }
}
