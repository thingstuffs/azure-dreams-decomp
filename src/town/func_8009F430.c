#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009CB64();                   /* extern */
extern M2C_UNK D_800F8A4C;

/* Initialize the object's action state using D_800F8A4C. */
void func_8009CB90(s32 object, s32 action, s32 state) {
    func_8009CB64(object, action, state, &D_800F8A4C);
}
