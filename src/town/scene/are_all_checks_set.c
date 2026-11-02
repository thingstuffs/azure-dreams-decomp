#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Return whether all checks from 0x147B through 0x1489 are nonzero. */
s32 are_all_checks_set(void) {
    s32 index;
    index = 1;
    while (get_script_flag_mask(index + 0x147A) != 0) {
        index += 1;
        if (index >= 0x10) {
            break;
        }
    }
    return index == 0x10;
}
