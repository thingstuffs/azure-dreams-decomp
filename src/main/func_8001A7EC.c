#include "common.h"

extern s32 func_80401444(void);
extern s32 func_804019A4(void);
extern void func_80400948(s32 arg0, s32 arg1);

extern s32 D_80409260[];
extern s32 D_80409268[];
extern s32 D_804094F8[];

/* Updates a slot's flag after four repeats of a nonzero state and returns the flag array. */
s32 *func_804017EC(void)
{
    s32 current_state;
    s32 slot_index;
    s32 one;

    current_state = func_80401444();
    if (current_state != 0) {
        slot_index = func_804019A4();
        if (D_80409268[slot_index] == current_state) {
            D_80409260[slot_index]++;
        } else {
            D_80409260[slot_index] = 0;
        }
        D_80409268[slot_index] = current_state;
        one = 1;
        if ((current_state == one) || (current_state == 4)) {
            if (D_80409260[slot_index] >= 4) {
                D_804094F8[slot_index] = one;
            }
        } else if (D_80409260[slot_index] >= 4) {
            D_804094F8[slot_index] = 0;
        }
        func_80400948(one, slot_index);
    }
    return D_804094F8;
}
