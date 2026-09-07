#include "common.h"

/* Marks slot (D_80081554 & 0xF) of the D_80083D98 registration table with a
   non-null sentinel, mirrors the masked index into D_80081558, advances the
   D_80081554 slot counter by one, then invokes two no-arg helper leaves. */
extern s32 D_80081554;
extern s32 D_80081558;
extern void *D_80083D98[32];

extern void func_8003528C(void);
extern void func_800352B4(void);

void func_8004E130(void)
{
    s32 idx;
    void **slot;

    idx = D_80081554 & 0xF;
    slot = &D_80083D98[idx];
    D_80081554 = idx;
    D_80081558 = idx;
    *slot = (void *)1;
    D_80081554 = idx + 1;
    func_8003528C();
    func_800352B4();
}
