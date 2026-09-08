#include "common.h"

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern s16 D_800814E8;
extern u8 D_80082E6E[9]; /* forced size>8 so gcc uses %hi/%lo, matching target addressing */

extern void func_80041CBC(void);
extern void func_8003D92C(void);
extern s16 func_8003F794(s32 a0, s32 a1);
extern void func_80040A88(int a0);
extern void func_80041C64(void);

/* If enabled, allocates a state slot as needed and registers the next callback; otherwise calls func_8003D92C. */
void func_80041BE4(void)
{
    func_80041CBC();
    if (D_80082E6E[0] != 0) {
        if (D_80083120[D_800814E8].field0 == 0) {
            D_800814E8 = func_8003F794(6, 8);
        }
        func_80040A88((int) func_80041C64);
    } else {
        func_8003D92C();
    }
}
