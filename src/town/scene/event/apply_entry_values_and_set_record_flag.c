#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/event.h"


/* Apply operation 0x5BC and the record code, then dispatch the record and context. */
void apply_entry_values_and_set_record_flag(Rec_func_800165F4_arg0 *record, s32 context) {
    clear_script_flag_bit(F_sbs11_pad25);
    set_script_flag_bit(record->unk_18);
    apply_selected_entry_values(record, context);
}
