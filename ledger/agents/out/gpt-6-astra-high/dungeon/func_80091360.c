#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"


/* Reset the record to state 0x34 with flag bit 0 cleared. */
void func_80096AC0(Rec_func_8008ACDC_arg0 *record) {
    record->unk_9A.as_s8 = 0x34;
    record->unk_9B.as_s8 = 0;
    record->unk_8C.as_s32 = 0;
    record->unk_A2 = (u16) (record->unk_A2 & 0xFFFE);
}
