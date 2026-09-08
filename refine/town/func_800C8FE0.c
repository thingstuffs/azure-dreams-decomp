#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800C6440(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_800C6C10();                      /* extern */


/* Decrement the record's countdown and run its expiry handlers when it reaches zero. */
void func_800C6740(Rec_func_80094268_arg0 *record, M2C_UNK forward_arg_1, M2C_UNK forward_arg_2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C6440(record);
        func_800C6C10(record);
        func_800C4174(record, forward_arg_1, forward_arg_2);
    }
}
