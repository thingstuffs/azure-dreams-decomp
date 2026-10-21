#include "common.h"

#include "common.h"
#include "engine/window.h"

extern s32 user_name_window_value[];

/* set_user_name_win stores the supplied name-window value. */
void set_user_name_win(s32 window_value) {
    user_name_window_value[0] = window_value;
}
