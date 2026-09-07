#include "common.h"

extern s32 func_80401444(void);
extern s32 func_804019A4(void);
extern void func_80400948(s32 arg0, s32 arg1);

extern s32 D_80409260[];
extern s32 D_80409268[];
extern s32 D_804094F8[];

s32 *func_804017EC(void)
{
    s32 state;
    s32 index;
    s32 one;

    state = func_80401444();
    if (state != 0) {
        index = func_804019A4();
        if (D_80409268[index] == state) {
            D_80409260[index]++;
        } else {
            D_80409260[index] = 0;
        }
        D_80409268[index] = state;
        one = 1;
        if ((state == one) || (state == 4)) {
            if (D_80409260[index] >= 4) {
                D_804094F8[index] = one;
            }
        } else if (D_80409260[index] >= 4) {
            D_804094F8[index] = 0;
        }
        func_80400948(one, index);
    }
    return D_804094F8;
}
