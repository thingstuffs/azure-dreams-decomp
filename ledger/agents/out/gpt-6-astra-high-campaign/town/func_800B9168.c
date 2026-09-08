#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

s32 func_800B68AC();                             /* extern */
M2C_UNK func_800B6E3C();                      /* extern */
extern M2C_UNK D_800B66E8;


/* Initializes the record, resolves its type data, and runs its setup routine. */
void func_800B68C8(Rec_func_800B683C_arg0 *record, s32 context, s16 type_id) {
    record->unk_08 = type_id;
    record->unk_04 = context;
    record->unk_0C = 0;
    record->unk_0E = 0;
    record->unk_00 = &D_800B66E8;
    record->unk_14 = func_800B68AC(record->unk_08);
    func_800B6E3C(record);
}
