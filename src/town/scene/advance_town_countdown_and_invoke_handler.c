#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
void func_8001886C(s32);                     /* extern */

/* Decrement the countdown and invoke handler 0x5FF when it reaches zero. */
void advance_town_countdown_and_invoke_handler(void) {
    u8 countdown;
    TownEventCursor *countdown_record;

    countdown_record = &((TownProgressState *)town_scene_root->event_data)->eventCursor;
    countdown = countdown_record->counter - 1;
    countdown_record->counter = countdown;
    if (!(countdown & 0xFF)) {
        func_8001886C(F_sbs13_pad06);
    }
}
