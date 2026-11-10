/* Reset the event buffer and advance the eight step counter.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_657800_80016000:80019114.
 * Only the strong PD gap is included; complete file edges remain unknown.
 */
#include "town/scene/event_cycle_reset_g00753.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Resets the town buffer and updates callback-dependent and default flags. */
void reset_buffer_and_event_flags(void) {
    D_80019118 = D_80018AF8;
    town_event_cycle_index = 0;

    if (town_scene_root->services->callback_054(4) != 0) {
        clear_script_flag_bit(F_sbs35_pad01);
    } else {
        set_script_flag_bit(F_sbs35_pad01);
    }

    if (town_scene_root->services->callback_054(4) != 0) {
        clear_script_flag_bit(F_sbs35_pad02);
    } else {
        set_script_flag_bit(F_sbs35_pad02);
    }

    if ((get_script_flag_mask(F_sbs35_pad01) != 0) &&
        (get_script_flag_mask(F_sbs35_pad02) != 0)) {
        set_script_flag_bit(F_sbs35_pad03);
    } else {
        clear_script_flag_bit(F_sbs35_pad03);
    }

    clear_script_flag_bit(F_sbs35_pad12);
    clear_script_flag_bit(F_sbs35_pad13);
    clear_script_flag_bit(F_sbs35_pad14);
    clear_script_flag_bit(F_sbs35_pad15);
    set_script_flag_bit(F_sbs35_pad16);
}

/* Increments D_80019114 and retains its low three bits, wrapping seven to zero. */
s32 advance_counter_modulo_eight(void)
{
    s32 index;

    index = (town_event_cycle_index + 1) & 7;
    town_event_cycle_index = index;
    return index;
}
