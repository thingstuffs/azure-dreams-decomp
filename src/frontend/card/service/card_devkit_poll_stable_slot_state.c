#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern s32 func_804019A4(void);
extern void func_804008A0(s32 index);

/* Tracks repeated states and updates the selected slot after state-specific delays. */
s32 card_devkit_poll_stable_slot_state(void)
{
    s32 state;
    s32 slot_index;
    s32 state_case;
    s32 state_offset;
    s32 *saved_state;

    state = card_devkit_dispatch_polled_event();
    slot_index = func_804019A4();
    if (state != 0) {
        if (D_80409258[slot_index] == state) {
            D_80409250[slot_index]++;
        } else {
            D_80409250[slot_index] = 0;
        }
        D_80409258[slot_index] = state;
        state_case = state - 1;
        switch (state_case) {
        case 0:
        case 1:
            state_offset = slot_index << 2;
            saved_state = (s32 *)((u8 *)D_804094F0 + state_offset);
            *saved_state = state;
            break;
        case 2:
            if (D_80409250[slot_index] >= 4) {
                D_804094F0[slot_index] = state;
            }
            break;
        case 4:
        case 3:
            if (D_80409250[slot_index] >= 11) {
                D_804094F0[slot_index] = state;
            }
            break;
        default:
            break;
        }
        func_804008A0(slot_index);
    }
    return state;
}
