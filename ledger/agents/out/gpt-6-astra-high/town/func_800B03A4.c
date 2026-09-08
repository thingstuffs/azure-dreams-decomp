#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AD7F8_arg0.h"

M2C_UNK func_80049490();                         /* extern */

/* Pass the record's base plus its index scaled by four to func_80049490. */
void func_800ADB04(Rec_func_800AD7F8_arg0 *record) {
    func_80049490(record->unk_20 + (record->unk_04 * 4));
}
