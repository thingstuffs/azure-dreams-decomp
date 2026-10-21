/* G00753: Reset the event buffer and advance the eight step counter.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_657800_80016000:80019114.
 * Only the strong PD gap is included; complete file edges remain unknown.
 */
#include "town/scene/event_cycle_reset_g00753.h"

/* Resets the town buffer and updates callback-dependent and default flags. */
void reset_buffer_and_event_flags(void) {
    D_80019118 = D_80018AF8;
    D_80019114 = 0;

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(F_sbs35_pad01);
    } else {
        func_80018548(F_sbs35_pad01);
    }

    if (D_80016000->unk_20->callback_054(4) != 0) {
        func_800185C0(F_sbs35_pad02);
    } else {
        func_80018548(F_sbs35_pad02);
    }

    if ((func_80018640(F_sbs35_pad01) != 0) &&
        (func_80018640(F_sbs35_pad02) != 0)) {
        func_80018548(F_sbs35_pad03);
    } else {
        func_800185C0(F_sbs35_pad03);
    }

    func_800185C0(F_sbs35_pad12);
    func_800185C0(F_sbs35_pad13);
    func_800185C0(F_sbs35_pad14);
    func_800185C0(F_sbs35_pad15);
    func_80018548(F_sbs35_pad16);
}

/* Advance the counter modulo eight. */
void advance_counter_modulo_eight(void)
{
    D_80019114 = (D_80019114 + 1) & 7;
}
