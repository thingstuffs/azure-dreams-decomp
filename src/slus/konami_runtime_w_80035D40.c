#include "common.h"

#include "common.h"

extern s32 D_8006ADB8;

/* set_user_name_win stores the supplied name-window value. */
void func_80035D40(s32 window_value) {
    D_8006ADB8 = window_value;
}
