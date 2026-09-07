#include "common.h"

extern s32 D_80028540[];
extern s32 D_80028548[];
extern s32 D_800287D8[];
extern s32 D_80084118[];

extern s32 func_80021410(void);
extern s32 func_8002190C(void);
extern void func_800209C4(void);

s32 *func_800217D4(void)
{
    s32 state;
    s32 index;

    state = func_80021410();
    if (state != 0) {
        index = func_8002190C();
        if (D_80028548[index] == state) {
            D_80028540[index]++;
        } else {
            D_80028540[index] = 0;
        }
        D_80028548[index] = state;
        if (state == 1 || state == 4) {
            s32 *count;

            count = &D_80028540[index];
            if (*count >= 4) {
                D_800287D8[index] = 1;
                *count = 0;
                D_80028548[index] = 0;
            }
        } else {
            s32 *count;

            D_80084118[index] = 0;
            count = &D_80028540[index];
            if (*count >= 4) {
                D_800287D8[index] = 0;
                *count = 0;
                D_80028548[index] = 0;
            }
        }
        func_800209C4();
    }
    return D_800287D8;
}
