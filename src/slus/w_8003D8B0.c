#include "common.h"

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern S_80083120 D_80083120[8];
extern int D_80082EC0[128];
extern int D_80083110[4];
extern volatile s16 D_80013714[6];

extern void func_8003DB4C(int *p, int n);
extern void func_800499BC(void);
extern void func_8004437C(s32 a0, s32 a1);
extern void func_8004425C(s32 a0);

/* Resets several global state blocks (dispatch table, a 512-byte buffer, a small
 * 4-word block, and a flag), then reinitializes some subsystem state and installs
 * default handlers via func_8004437C/func_8004425C. */
void func_8003D8B0(void)
{
    s32 i;

    func_8003DB4C((int *)D_80083120, 0x10);
    func_8003DB4C(D_80082EC0, 0x80);

    {
        int *p = D_80083110;
        for (i = 3; i >= 0; i--) {
            *(p + i) = 0;
        }
    }

    D_80013714[0] = 0;

    func_800499BC();
    func_8004437C(0x2A, 0);
    func_8004425C(0);
}
