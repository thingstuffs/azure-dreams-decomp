/* Reset event state and dispatch the next eligible event.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_8059E8A0, PD:town/ll34_51e000_80016000:80019088.
 * Only the two strong CL/PD gaps are included; complete file edges remain unknown.
 */
#include "town/scene/event_state_dispatch_g00731.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Return whether both checks for 0x1200 and 0x1201 return zero. */
s32 check_town_event_flags_clear(void) {
    s32 result;
    s32 return_value;

    if (get_script_flag_mask(Fp_bibian_pool_event) == 0) {
        result = get_script_flag_mask(Fp_mia_pool_event);
        return_value = 1;
        if (result == 0) {
            return return_value;
        }
    }
    return_value = 0;
    return return_value;
}

/* Passes seven table-selected event IDs and three fixed event flags to func_800188E4. */
void reset_town_event_state(void) {
    s16 *tableEntry;
    s32 entryCount;

    entryCount = 0;
    tableEntry = (s16 *)D_80019088;
    do {
        s32 entryValue = *tableEntry;

        tableEntry += 4;
        entryCount += 1;
        clear_script_flag_bit(entryValue);
    } while (entryCount < 7);

    clear_script_flag_bit(F_sbs13_pad21);
    clear_script_flag_bit(F_sbs13_pad13);
    clear_script_flag_bit(F_sbs13_pad24);
}

/* Advance through town events and dispatch the next eligible entry. */
void advance_town_events_and_dispatch_entry(void)
{
    TownEntry *event_entry;
    TownEventCursor *event_state;
    s32 checked_count;

    event_state = &town_scene_root->event_data->eventCursor;
    event_state->eventIndex += 1;
    event_state->eventIndex %= 7;
    reset_town_event_state();

    if (check_town_event_flags_clear() != 0) {
        checked_count = 0;
        do {
            if ((get_script_flag_mask(D_80019088[event_state->eventIndex].check) == 0) !=
                (D_80019088[event_state->eventIndex].enabled != 0)) {
                event_entry = &D_80019088[event_state->eventIndex];
                set_script_flag_bit(event_entry->event);
                break;
            }

            event_state->eventIndex += 1;
            event_state->eventIndex %= 7;
            checked_count += 1;
        } while (checked_count < 7);

        if (event_state->eventIndex != 5) {
            set_script_flag_bit(F_sbs13_pad21);
        }
        set_script_flag_bit(F_sbs13_pad13);
    }
}
