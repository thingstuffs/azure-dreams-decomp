#include "common.h"

extern s32 func_804015D8(void);
extern s32 func_804019A4(void);
extern void func_804008A0(s32 index);

extern s32 D_80409250[];
extern s32 D_80409258[];
extern s32 D_804094F0[];
extern void *D_8040007C[];

/* Tracks repeated states and updates the selected slot after state-specific delays. */
s32 func_804016D0(void)
{
    s32 state;
    s32 slot_index;
    s32 state_case;
    s32 state_offset;
    s32 *saved_state;
    static void *const label_owners[] = {
        &&state_one,
        &&state_two,
        &&state_three,
        &&done,
        &&done,
    };

    (void)label_owners;
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
        if ((u32)state_case >= 5) {
            goto done;
        }
        goto *D_8040007C[state_case];

state_one:
        state_offset = slot_index << 2;
        saved_state = (s32 *)((u8 *)D_804094F0 + state_offset);
        *saved_state = state;
        goto done;

state_two:
        if (D_80409250[slot_index] >= 4) {
            D_804094F0[slot_index] = state;
        }
        goto done;

state_three:
        if (D_80409250[slot_index] >= 11) {
            D_804094F0[slot_index] = state;
        }

done:
        func_804008A0(slot_index);
    }
    return state;
}
