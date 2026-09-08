#include "common.h"

extern void func_800214A4(void);
extern s32 func_80069C08(s32 arg0);
extern s32 D_800287C8[];
extern s32 D_800287CC;
extern s32 D_800287E0;

/* Processes state 2, returning 5 on reset or advancing to state 3. */
s32 func_8002121C(void)
{
    s32 status;

    status = 0;
    if (D_800287C8[0] == 2) {
        func_800214A4();
        if (func_80069C08(D_800287CC) == 0) {
            D_800287C8[0] = 0;
            status = 5;
        } else {
            D_800287E0 = 0;
            D_800287C8[0]++;
        }
    }
    return status;
}
