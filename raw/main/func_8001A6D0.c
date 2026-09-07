#include "common.h"

extern s32 func_804015D8(void);
extern s32 func_804019A4(void);
extern void func_804008A0(s32 index);

extern s32 D_80409250[];
extern s32 D_80409258[];
extern s32 D_804094F0[];
extern void *D_8040007C[];

s32 func_804016D0(void)
{
    s32 state;
    s32 index;
    s32 dispatch;
    s32 offset;
    s32 *destination;
    static void *const label_owners[] = {
        &&state_one,
        &&state_two,
        &&state_three,
        &&done,
        &&done,
    };

    (void)label_owners;
    state = func_804015D8();
    index = func_804019A4();
    if (state != 0) {
        if (D_80409258[index] == state) {
            D_80409250[index]++;
        } else {
            D_80409250[index] = 0;
        }
        D_80409258[index] = state;
        dispatch = state - 1;
        if ((u32)dispatch >= 5) {
            goto done;
        }
        goto *D_8040007C[dispatch];

state_one:
        offset = index << 2;
        destination = (s32 *)((u8 *)D_804094F0 + offset);
        *destination = state;
        goto done;

state_two:
        if (D_80409250[index] >= 4) {
            D_804094F0[index] = state;
        }
        goto done;

state_three:
        if (D_80409250[index] >= 11) {
            D_804094F0[index] = state;
        }

done:
        func_804008A0(index);
    }
    return state;
}
