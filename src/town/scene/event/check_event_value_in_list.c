#include "common.h"

extern u8 town_event_value_list[];

/* Check whether the zero-terminated byte list contains the target value. */
s32 check_event_value_in_list(s32 target_value) {
    s32 i = 0;

    while (town_event_value_list[i] != 0) {
        if (target_value == town_event_value_list[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
