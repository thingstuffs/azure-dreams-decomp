#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80034FFC();                   /* extern */
extern M2C_UNK D_80082A38;

/* Pass the global object D_80082A38 to func_80034FFC. */
void func_800352FC(void) {
    func_80034FFC(&D_80082A38);
}
