#include "common.h"

extern s32 D_8001E954[];
extern s32 check_object_callback_returns_two(void);

s32 get_progress_status_code(void) {
    s32 value;
    if (D_8001E954[0] == 0) {
        return 0;
    }
    value = check_object_callback_returns_two();
    if (value != 0) {
        return 2;
    }
    return 1;
}
