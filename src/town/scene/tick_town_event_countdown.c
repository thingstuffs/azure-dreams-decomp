#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Decrement the countdown and invoke handler 0x5FF when it reaches zero. */
void tick_town_event_countdown(void) {
    u8 countdown;
    TownEventCursor *countdown_record;

    countdown_record = &town_scene_root->event_data->eventCursor;
    countdown = countdown_record->counter - 1;
    countdown_record->counter = countdown;
    if (!(countdown & 0xFF)) {
        set_script_flag_bit(F_sbs13_pad06);
    }
}
