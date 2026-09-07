#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_8009803C;
extern M2C_UNK D_800D01A0;


void func_80098FBC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1) {
    func_80094984(&D_800D01A0, arg0);
    D_80082668 = 0;
    arg0->unk_04.as_pm = &D_8009803C;
    arg0->unk_0A.as_s16 = 0x15;
    func_80099754(arg1);
}
