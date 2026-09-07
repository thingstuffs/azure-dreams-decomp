#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern u8 D_80082660;
extern M2C_UNK D_8009AA2C;
extern M2C_UNK D_800D00A8;


void func_80098F48(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1) {
    func_80094984(&D_800D00A8, arg0);
    *((arg0->unk_40 * 8) + &D_80082660) = 0;
    arg0->unk_0A.as_s16 = 0xA;
    func_80099754(arg1);
    arg0->unk_04.as_pm = &D_8009AA2C;
}
