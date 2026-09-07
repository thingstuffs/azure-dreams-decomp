#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003BAF8();                         /* extern */
s32 func_800B2834();                                /* extern */
extern M2C_UNK D_8006AFE8[];

/* Pass the selected table entry to func_8003BAF8. */
void func_8003BA24(void) {
    func_8003BAF8(D_8006AFE8[func_800B2834()]);
}
