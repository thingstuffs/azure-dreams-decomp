#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"

M2C_UNK func_80022BE8();                      /* extern */
extern u8 D_800280B4[];
__asm__(".set D_800280B4, 0x800280B4");


/* Initialize record fields and process the selected table entry. */
void func_80022C48(Rec_func_8002290C_arg0 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20) {
    record->unk_14 = value_14;
    record->unk_20 = value_20;
    record->unk_08 = entry_index;
    record->unk_0C = value_0c;
    func_80022BE8((entry_index * 0x18) + &D_800280B4[0]);
}
