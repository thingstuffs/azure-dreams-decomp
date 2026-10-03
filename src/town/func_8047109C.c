#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


M2C_UNK func_80017F3C();                   /* extern */
M2C_UNK func_80018824();          /* extern */
extern M2C_UNK D_8001B218;
extern s32 D_8001B318;

/* Prepares D_8001B218, passes it to the active object's callback, and saves the result. */
void func_8001809C(void) {
    func_80018824(&D_8001B218, 0x100);
    func_80017F3C(&D_8001B218);
    D_8001B318 = D_80016000->unk_20->callback_068(0, 0, 1, &D_8001B218);
}
