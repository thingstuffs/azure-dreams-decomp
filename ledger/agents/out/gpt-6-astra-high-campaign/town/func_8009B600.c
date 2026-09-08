#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_800981D4;
extern M2C_UNK D_800D0090;


/* Initialize the record and set its handler and initial value. */
void func_80098D60(Rec_func_80094268_arg0 *record, M2C_UNK setup_value, M2C_UNK init_context) {
    func_80099754(setup_value);
    func_80094984(&D_800D0090, record, init_context);
    record->unk_04.as_pm = &D_800981D4;
    record->unk_10.as_s16 = 0x800;
}
