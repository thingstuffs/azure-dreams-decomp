#include "common.h"
#include "m2c_compat.h"

s32 func_80019DFC(); /* extern */
void func_8001ACE8();                     /* extern */
extern M2C_UNK D_8001BB44;
extern M2C_UNK D_8001C358;

/* Process ID 0x145C and dispatch through D_8001BB44 and D_8001C358. */
void func_80017104(s32 dispatch_value, s32 unused, s32 dispatch_context) {
    func_8001ACE8(0x145C);
    func_80019DFC(&D_8001BB44, &D_8001C358, dispatch_value, dispatch_context);
}
