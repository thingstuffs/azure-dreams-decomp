#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

void func_800949C4(u8 *sourceBytes, s32 selection, u8 *destination);                         /* extern */


/* Stores the value in the record and forwards it with unk_10 to func_800949C4. */
void func_80094A38(s32 value, Rec_D_80082D58 *record, u8 *destination) {
    record->unk_1C = value;
    func_800949C4((u8 *)value, record->unk_10, destination);
}
