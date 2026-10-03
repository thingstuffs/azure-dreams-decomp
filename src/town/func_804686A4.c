#include "shared/town_event_state.h"
#include "common.h"

extern void func_8001E5F0(s32 arg0);

/* Clear two state bytes and process five fixed identifiers. */
void func_800196A4(void) {
    D_8001E950->dispatchState = 0;
    D_8001E950->unk_06 = 0;
    func_8001E5F0(0x400);
    func_8001E5F0(0x401);
    func_8001E5F0(0x402);
    func_8001E5F0(0xA0);
    func_8001E5F0(0xA1);
}
