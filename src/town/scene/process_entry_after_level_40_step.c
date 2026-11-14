#include "common.h"
#include "town/scene.h"
#include "town/player.h"

extern s32 func_800178D0(void);

/* Runs func_800178D0 when func_800187FC is at least 40, then forwards both values to func_80017978. */
void process_entry_after_level_40_step(s32 first_value, s32 second_value, s32 unused_value) {
    if (get_town_state_count() >= 40) {
        func_800178D0();
    }
    process_checked_entry(first_value, second_value);
}
