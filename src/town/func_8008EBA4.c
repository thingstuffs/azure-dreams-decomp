#include "common.h"

/* Sibling of func_8004F52C/func_8004EE90/func_800510DC (D_800814A0 "used"/
 * flags word family). Reuses ONE lui-computed base register across the
 * load and store of D_800814A0 (no second lui) -- per code10.c that shape
 * needs gcc>=2.8 (2.8.0/2.8.1/2.95.2) or 2.7.2-cdk; adjacent sibling
 * func_8008EC14 (this container, immediately following) matched at 2.8.1. */
extern void func_8008C28C(s32 a0);

typedef struct {
    s32 val;
    s32 pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

extern void *D_800CFCA8[];

void func_8008C304(s32 *arg0)
{
    s32 temp;

    func_8008C28C(*arg0);
    temp = *arg0 + 1;
    *arg0 = temp;
    if (temp >= 0x80) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800CFCA8[0] = 0;
        D_800814A0.val |= 0x8000;
    }
}
