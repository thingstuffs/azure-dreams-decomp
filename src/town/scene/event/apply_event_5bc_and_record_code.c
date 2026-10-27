#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

s32 *func_80017D80();             /* extern */

typedef struct S_8051EE00_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051EE00_0;   /* arg0 in apply_event_5bc_and_record_code */

/* Apply operation 0x5BC and the record code, then dispatch the record and context. */
void apply_event_5bc_and_record_code(S_8051EE00_0 *record, s32 context) {
    func_80018ADC(F_sbs11_pad25);
    func_80018A64(record->unk_18);
    func_80017D80(record, context);
}
