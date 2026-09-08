#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"



/* Sets the record's byte at offset 0x03. */
void func_80035060(Rec_D_80082A38 *record, s8 value) {
    record->unk_03 = value;
}
