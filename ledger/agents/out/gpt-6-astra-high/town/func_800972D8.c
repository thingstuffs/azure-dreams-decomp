#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_800949C4();                         /* extern */


/* Stores the value in the record and forwards it with unk_10 to func_800949C4. */
void func_80094A38(s32 value, Rec_D_80082D58 *record) {
    record->unk_1C = value;
    func_800949C4(value, record->unk_10);
}
