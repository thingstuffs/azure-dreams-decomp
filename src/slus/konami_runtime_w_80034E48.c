#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK ClearImage(); /* extern */
M2C_UNK func_80034EB4();                   /* extern */
M2C_UNK func_80034EC4();                   /* extern */
M2C_UNK func_8003C920();                            /* extern */
extern M2C_UNK D_800809A8;
extern M2C_UNK D_800809B0;
extern M2C_UNK D_80082A38;

void func_80034E48(void) {
    func_8003C920();
    func_80034EB4(&D_80082A38);
    func_80034EC4(&D_80082A38);
    ClearImage(&D_800809A8, 0, 0, 0);
    ClearImage(&D_800809B0, 0, 0, 0);
}
