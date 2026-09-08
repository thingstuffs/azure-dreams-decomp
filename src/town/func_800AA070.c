#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033CD8();                   /* extern */
extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800A7774[3];


/* Decrement the countdown and reset the record data and handler when it expires. */
void func_800A77D0(Rec_func_80094268_arg0 *record) {
    u16 countdown;

    countdown = record->unk_90.as_u16 - 1;
    record->unk_90.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_80033CD8(record, &D_80045340[0]);
        record->unk_90.as_u16 = 0xAU;
        record->unk_50.as_pm = &D_800A7774[0];
    }
}
