#include "common.h"

extern void ClearImage(void *, s32, s32, s32);
extern void func_8003D7DC(void);
extern void func_8004EB30(void);
extern void ResetCallback(void);
extern s32 D_80080A7C;
extern void *D_80081480;
extern void *D_8008148C;
extern s32 D_80126804;

void func_8003D760(void)
{
    s32 rect[2];

    ResetCallback();
    func_8004EB30();
    func_8003D7DC();
    rect[0] = 0;
    rect[1] = 0x02000400;
    ClearImage(rect, 0, 0, 0);
    D_8008148C = &D_80126804;
    D_80081480 = &D_80126804;
    D_80080A7C = 0x38000;
}
