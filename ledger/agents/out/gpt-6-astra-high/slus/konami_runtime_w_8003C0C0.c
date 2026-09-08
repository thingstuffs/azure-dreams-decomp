#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082D58.h"



/* Clears the record's unk_04 field. */
void func_8003C0C0(Rec_D_80082D58 *record) {
    record->unk_04 = 0;
}
