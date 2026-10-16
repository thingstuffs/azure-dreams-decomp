#include "shared/town_event_state.h"
#include "common.h"

extern void townResetDispatchStateAndFlags(void);

/* Call townResetDispatchStateAndFlags, increment the byte at D_8001E950, and return zero. */
s32 func_800193DC(s32 first_value, s32 second_value) {
    townResetDispatchStateAndFlags();
    D_8001E950->unk_00 += 1;
    return 0;
}
