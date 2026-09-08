#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019DFC(); /* extern */
M2C_UNK func_8001ACE8();                     /* extern */
extern M2C_UNK D_8001BB44;
extern M2C_UNK D_8001C358;

/* Process ID 0x145C and dispatch through D_8001BB44 and D_8001C358. */
void func_80017104(s32 dispatch_value, M2C_UNK unused, M2C_UNK dispatch_context) {
    func_8001ACE8(0x145C);
    func_80019DFC(&D_8001BB44, &D_8001C358, dispatch_value, dispatch_context);
}
