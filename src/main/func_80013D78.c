#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800269B4();                         /* extern */
M2C_UNK func_80026B18();   /* extern */
M2C_UNK func_80026C94(s32);                            /* extern */
M2C_UNK func_80026CF0();                         /* extern */
extern M2C_UNK D_8002807C;
extern M2C_UNK D_80028084;

/* Update the record using the two shared data addresses. */
void func_80026D78(s32 record_addr) {
    func_80026C94(record_addr);
    func_80026CF0(record_addr);
    func_80026B18(record_addr, &D_8002807C, &D_80028084);
    func_800269B4(record_addr);
}
