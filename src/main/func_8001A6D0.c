#include "common.h"

extern s32 func_804015D8(void);
extern s32 func_804019A4(void);
extern void func_804008A0(s32 index);

extern s32 D_80409250[];
extern s32 D_80409258[];
extern s32 D_804094F0[];

/* Tracks repeated states and updates the selected slot after state-specific delays. */
s32 func_804016D0(void)
{
    s32 state;
    s32 slot_index;
    s32 state_case;
    s32 state_offset;
    s32 *saved_state;

    state = func_804015D8();
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
            state_offset = slot_index << 2;
            saved_state = (s32 *)((u8 *)D_804094F0 + state_offset);
            *saved_state = state;
            break;
        case 1:
            if (D_80409250[slot_index] >= 4) {
                D_804094F0[slot_index] = state;
            }
            break;
        case 2:
            if (D_80409250[slot_index] >= 11) {
                D_804094F0[slot_index] = state;
            }
            break;
        case 3:
        case 4:
        default:
            break;
        }
        func_804008A0(slot_index);
    }
    return state;
}
