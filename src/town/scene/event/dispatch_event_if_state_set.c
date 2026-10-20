#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"

extern void func_8001E578(s32 id);

/* Dispatch event 0x402 when the state byte is nonzero. */
s32 dispatch_event_402_if_state_set(void) {
    if (D_8001E950->dispatchState == 0) {
        return 0;
    }
    func_8001E578(F_sbs01_pad13);
    return 1;
}
