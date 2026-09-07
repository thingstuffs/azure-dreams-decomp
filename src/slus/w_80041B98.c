#include "common.h"

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern s16 D_800814E8;

extern void func_80041CBC(void);
extern void func_80040A88(int a0);
extern void func_80041BE4(void);

/* If the current state-table slot's flag is clear, calls func_80041CBC() then registers func_80041BE4 as the next state callback. */
void func_80041B98(void)
{
    func_80041CBC();
    if (D_80083120[D_800814E8].field0 == 0) {
        func_80040A88((int)func_80041BE4);
    }
}
