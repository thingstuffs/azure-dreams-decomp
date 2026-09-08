#include "common.h"

extern s32 D_800CF874;

/* reserve_tw_mon_load: stores the door-opening demo setting. */
void func_8008B550(s32 demo_setting) {
    D_800CF874 = demo_setting;
}
