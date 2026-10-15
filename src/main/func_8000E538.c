#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"

M2C_UNK TestEvent();                         /* extern */






/* Clear the event status and test the four event handles. */
void func_80021538(void) {
    (*(s32 *)(&D_800287E4)) = 0;
    TestEvent((*(s32 *)(&D_80028560)));
    TestEvent((*(s32 *)(&D_80028564)));
    TestEvent((*(s32 *)(&D_80028568)));
    TestEvent((*(s32 *)(&D_8002856C)));
}
