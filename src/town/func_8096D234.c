#include "common.h"

extern void func_8004B248(void *arg0);
extern void func_80051228(void);
extern int D_800814A0;

// Set the linked object's flag, process the embedded data, and signal an update.
void func_801256CC(void *object)
{
    void *linkedObject;

    linkedObject = *(void **)object;
    *(u16 *)((u8 *)linkedObject + 0x1E) =
        (u16)(*(u16 *)((u8 *)linkedObject + 0x1E) | 0x2000);
    func_8004B248((u8 *)object + 0x5C);
    *(u16 *)((u8 *)object - 2) =
        (u16)(*(u16 *)((u8 *)object - 2) | 0x8000);
    D_800814A0 |= 0x8000;
    func_80051228();
}
