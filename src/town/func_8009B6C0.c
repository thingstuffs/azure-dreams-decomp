#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D00A0;


void func_80098E20(Rec_func_80094268_arg0 *arg0) {
    func_80094984(&D_800D00A0, arg0);
    D_80082668 = 0;
    arg0->unk_04.as_pm = &D_80098078;
    arg0->unk_0A.as_s16 = 8;
}
