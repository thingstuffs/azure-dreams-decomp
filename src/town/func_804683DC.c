#include "shared/town_event_state.h"
#include "common.h"

extern void func_800196A4(void);

/* Call func_800196A4, increment the byte at D_8001E950, and return zero. */
s32 func_804683DC(s32 first_value, s32 second_value) {
    func_800196A4();
    D_8001E950->unk_00 += 1;
    return 0;
}
