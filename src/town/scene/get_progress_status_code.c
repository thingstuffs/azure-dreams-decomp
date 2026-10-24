#include "common.h"

extern s32 town_selected_valid_entry[];
extern s32 check_object_callback_returns_two(void);

/* Returns zero for an empty D_8001E954 entry, two when the callback test succeeds, or one otherwise. */
s32 get_progress_status_code(void) {
    s32 value;
    if (town_selected_valid_entry[0] == 0) {
        return 0;
    }
    value = check_object_callback_returns_two();
    if (value != 0) {
        return 2;
    }
    return 1;
}
