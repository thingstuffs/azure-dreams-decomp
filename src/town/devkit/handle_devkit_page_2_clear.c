#include "common.h"
#include "town/devkit.h"
#include "town/scene.h"

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern State *devkit_state_slots[3];

/* Devkit page 2: pass the value through while the page is idle; otherwise clear its flag, set state flag 0x20 and rescan. */
s32 handle_devkit_page_2_clear(s32 value)
{
    s32 result;

    if (check_devkit_secondary_condition(2) == 0) {
        set_devkit_flag_by_index(2);
        result = value;
    } else {
        clear_devkit_flag_for_index(2);
        devkit_state_slots[0]->flags |= 0x20;
        result = call_indexed_callback_failed_test();
    }
    return result;
}
