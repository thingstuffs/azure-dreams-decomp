#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))




extern void *select_event_data_table();

/* Checks the active event and dispatches the 0x27/0x200 handler when matched. */
s32 dispatch_active_event_27(void) {
    TownEventArgumentPair16 *event;

    if ((u8) D_8001E950->dispatchState < 2U) {
        event = select_event_data_table(D_8001E950->dispatchState,
                              D_8001E950->unk_05);
        if (event->unk_00 == 0x27) {
            if (event->unk_02 == 0x200) {
                D_80016000->unk_20->callback_2F8(0x27, 0x200);
            }
        }
        return 1;
    }
    return 0;
}
