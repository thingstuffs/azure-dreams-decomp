#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008D024_arg0.h"


/* Set the record's state to 0x21 and clear its associated fields. */
void func_8008D330(Rec_func_8008D024_arg0 *record) {
    record->unk_9A = 0x21;
    record->unk_9B.as_s8 = 0;
    record->unk_8C = 0;
}
