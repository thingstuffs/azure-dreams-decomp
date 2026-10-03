#include "shared/town_event_state.h"
#include "common.h"

extern void func_8001E578(s32);

/* Set three state bytes to 2 and dispatch event 0xA2. */
void func_8001C108(void) {
    D_8001E950->unk_00 = 2;
    D_8001E950->unk_05 = 2;
    D_8001E950->dispatchState = 2;
    func_8001E578(0xA2);
}
