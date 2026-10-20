#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
void func_800177C4(s32);                     /* extern */


/* Dispatches mode 2, then invokes the handler for 0x596. */
void run_service_1f4_then_event_596(void) {
    D_80016000->unk_20->callback_1F4(2);
    func_800177C4(F_sbs10_pad30);
}
