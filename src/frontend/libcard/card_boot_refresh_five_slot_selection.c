/* family_delay_slot fixture - row foff 0x262030 [main], true base 0x80025030.
 * The row's rowbase record already fires (true base 0x80025030), so retail word 24
 * `j 0x250a4` is the FUNCTION-LOCAL if/else join jump (base + 0x74 = word 29).
 * The wave candidate still modelled it as a fake noreturn extern func_800250A4();
 * maspsx LEAD 18 flips jal->j but a CALL's delay slot can never hold the join's
 * first insn, so word 25 stayed `nop` where retail has `addiu $s0,$s0,4` (gcc dbr
 * steal-from-thread + redirect-to-target+4).  Written as a real if/else, gcc emits
 * the jump itself and fills the slot.
 */
#include "common.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

/* Refresh the slot menu: highlight the selected command unless the slot row has focus, mark the selected one of the five slots and update the slot details. */
void card_boot_refresh_five_slot_selection(CardSlotMenuState *state) {
    s32 highlight;
    s32 i;

    if (state->unk_48 == 1) {
        highlight = 1;
    } else {
        card_boot_begin_selected_value_transition(state->command_panel, state->selected_command);
        highlight = 0;
    }
    for (i = 0; i < 5; i++) {
        if (i == state->unk_28) {
            card_boot_set_slot_selection_marker(state->slots[i], highlight);
        } else {
            card_boot_clear_slot_selection_marker(state->slots[i]);
        }
    }
    card_boot_set_slot_details_selection(state->slot_details, state->unk_28, state->selected_command);
}
