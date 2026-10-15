#include "modules/main_server_ship.h"
#include "common.h"







/* Store a value and its converted result in the selected state slot. */
void func_800220DC(void) {
    s32 state_index;
    s32 source_value;

    state_index = (*(s32 *)(&D_800287CC)) != 0;
    source_value = func_8002191C();
    D_80084128[state_index] = source_value;
    D_80084120[state_index] = func_800219B8(source_value);
}
