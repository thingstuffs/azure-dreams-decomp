#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C4174();    /* extern */
void func_800C6440(Rec_func_80094268_arg0 *);                            /* extern */
s32 func_800C6C10();                      /* extern */


/* Decrement the record's countdown and run its expiry handlers when it reaches zero. */
void func_800C6740(Rec_func_80094268_arg0 *record, s32 forward_arg_1, s32 forward_arg_2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800C6440(record);
        func_800C6C10(record);
        func_800C4174(record, forward_arg_1, forward_arg_2);
    }
}
