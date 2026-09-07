#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800269B4();                         /* extern */
M2C_UNK func_80026B18();   /* extern */
M2C_UNK func_80026C94();                            /* extern */
M2C_UNK func_80026CF0();                         /* extern */
extern M2C_UNK D_8002807C;
extern M2C_UNK D_80028084;

void func_80026D78(s32 arg0) {
    func_80026C94();
    func_80026CF0(arg0);
    func_80026B18(arg0, &D_8002807C, &D_80028084);
    func_800269B4(arg0);
}
