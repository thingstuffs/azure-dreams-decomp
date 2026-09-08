#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"



/* Clears the record fields at offsets 0x00, 0x01, and 0x34. */
void func_80034EB4(Rec_D_80082A38 *record) {
    record->unk_00 = 0;
    record->unk_01 = 0;
    record->unk_34 = 0;
}
