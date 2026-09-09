#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK SD_Call();                     /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_80091AF0;
extern M2C_UNK D_800D00E8;


/* Initialize the record with its handler and a count of twelve. */
void func_800940D0(Rec_func_80094268_arg0 *record, M2C_UNK unused, M2C_UNK setup_value) {
    SD_Call(0x510);
    func_80094984(&D_800D00E8, record, setup_value);
    record->unk_00.as_pm = &D_80091AF0;
    record->unk_0A.as_s16 = 0xC;
}
