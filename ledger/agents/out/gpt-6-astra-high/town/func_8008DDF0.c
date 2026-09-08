#include "common.h"

extern s32 D_800CF874;

/* door_open_demo_set_sub: stores the door-opening demo setting. */
void func_8008B550(s32 demo_setting) {
    D_800CF874 = demo_setting;
}
