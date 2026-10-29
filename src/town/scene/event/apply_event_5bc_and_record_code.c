#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/event.h"


/* Apply operation 0x5BC and the record code, then dispatch the record and context. */
void apply_event_5bc_and_record_code(Rec_func_800165F4_arg0 *record, s32 context) {
    func_80018ADC(F_sbs11_pad25);
    func_80018A64(record->unk_18);
    func_80017D80(record, context);
}
