#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

M2C_UNK func_8003DB94(); /* extern */
M2C_UNK func_8008F01C();  /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0678;
extern M2C_UNK D_800D0690;
extern M2C_UNK D_800ED15C;


void func_800C6180(Rec_D_800CFCB4 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8003DB94(arg2, &D_800ED15C, 0);
    func_8008F01C(arg0, arg1, &D_800D0678);
    func_8009B218(arg0, arg1, arg2, &D_800D0690);
    arg0->unk_4D.as_s8 = 0xD;
    arg0->unk_4C = 7;
}
