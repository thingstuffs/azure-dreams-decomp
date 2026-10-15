#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Clears (*(s32 *)(&D_800287C8)) and runs func_800214A4. */
void func_80020A0C(void) {
    (*(s32 *)(&D_800287C8)) = 0;
    func_800214A4();
}
