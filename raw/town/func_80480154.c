#include "common.h"

extern void *D_80016000;
extern s32 D_800189BC[];
extern s32 D_80019548[];
extern void func_80016540(void);

void func_80480154(void)
{
    func_80016540();
    D_80019548[0] = D_800189BC[*(s32 *)((u8 *)D_80016000 + 8)];
}
