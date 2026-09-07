#include "common.h"

extern void func_8004B248(void *arg0);
extern void func_80051228(void);
extern int D_800814A0;

void func_801256CC(void *arg0)
{
    void *temp_v1;

    temp_v1 = *(void **)arg0;
    *(u16 *)((u8 *)temp_v1 + 0x1E) =
        (u16)(*(u16 *)((u8 *)temp_v1 + 0x1E) | 0x2000);
    func_8004B248((u8 *)arg0 + 0x5C);
    *(u16 *)((u8 *)arg0 - 2) =
        (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
    D_800814A0 |= 0x8000;
    func_80051228();
}
