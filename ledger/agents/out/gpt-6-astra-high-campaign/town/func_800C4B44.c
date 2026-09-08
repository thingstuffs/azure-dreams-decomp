#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E4FC(); /* extern */
M2C_UNK func_8003F320();                            /* extern */
extern M2C_UNK D_800D4740;

/* Initialize D_800D4740 with selector 6 and run the follow-up setup. */
void func_800C22A4(void) {
    func_8003E4FC(6, &D_800D4740, 0);
    func_8003F320();
}
