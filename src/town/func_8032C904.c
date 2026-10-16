#include "common.h"
#include "m2c_compat.h"

s32 townApplyEntryPosition(); /* extern */
void townSetScriptFlagBit();                     /* extern */
extern M2C_UNK D_8001BB44;
extern M2C_UNK D_8001C358;

/* Process ID 0x145C and dispatch through D_8001BB44 and D_8001C358. */
void townProcessEvent145CAndDispatch(s32 dispatch_value, s32 unused, s32 dispatch_context) {
    townSetScriptFlagBit(0x145C);
    townApplyEntryPosition(&D_8001BB44, &D_8001C358, dispatch_value, dispatch_context);
}
