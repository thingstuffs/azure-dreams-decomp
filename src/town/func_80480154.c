#include "common.h"

extern void *D_80016000;
extern s32 D_800189BC[];
extern s32 D_80019548[];
extern void func_80016540(s32, s32);

void func_80480154(s32 arg0, s32 arg1)
{
    func_80016540(arg0, arg1);
    D_80019548[0] = D_800189BC[*(s32 *)((u8 *)D_80016000 + 8)];
}
