#include "common.h"

extern s32 D_80028540[];
extern s32 D_80028548[];
extern s32 D_800287D8[];
extern s32 D_80084118[];

extern s32 func_80021410(void);
extern s32 func_8002190C(void);
extern void func_800209C4(void);

/* Updates the indexed flag after four consecutive repeats of a nonzero state. */
s32 *func_800217D4(void)
{
    s32 current_state;
    s32 state_index;

    current_state = func_80021410();
    if (current_state != 0) {
        state_index = func_8002190C();
        if (D_80028548[state_index] == current_state) {
            D_80028540[state_index]++;
        } else {
            D_80028540[state_index] = 0;
        }
        D_80028548[state_index] = current_state;
        if (current_state == 1 || current_state == 4) {
            s32 *repeat_count;

            repeat_count = &D_80028540[state_index];
            if (*repeat_count >= 4) {
                D_800287D8[state_index] = 1;
                *repeat_count = 0;
                D_80028548[state_index] = 0;
            }
        } else {
            s32 *repeat_count;

            D_80084118[state_index] = 0;
            repeat_count = &D_80028540[state_index];
            if (*repeat_count >= 4) {
                D_800287D8[state_index] = 0;
                *repeat_count = 0;
                D_80028548[state_index] = 0;
            }
        }
        func_800209C4();
    }
    return D_800287D8;
}
