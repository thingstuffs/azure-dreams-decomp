/* cfail-repair: unary-star typing only */
#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK change_map();
extern s32 get_player_homerank();
extern M2C_UNK func_800B28A0();

void func_800A0B74(void *arg0, s32 *arg1) {
    u8 temp_v1;

    temp_v1 = *((u8 *)((s8 *)arg0 + 0x96));
    if (temp_v1 == 0) {
        arg0 = arg1;
    } else {
        s32 temp_v0;

        if (temp_v1 == 1) {
            temp_v0 = func_800B28A0();
        } else {
            temp_v0 = get_player_homerank();
        }
        arg0 = (void *)arg1[temp_v0];
    }
    change_map(arg0);
}
