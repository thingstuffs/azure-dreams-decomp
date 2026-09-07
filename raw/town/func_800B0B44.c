#include "common.h"

typedef struct FuncArg {
    u8 pad0[4];
    s32 field4;
    u8 pad8[0x20];
    s32 field28;
    s32 field2C;
} FuncArg;

extern void func_800AE148(void *arg0);
extern void func_800B1718(s32 arg0);
extern void func_800B1DBC(s32 arg0);
extern s32 D_800814A0[];
extern s32 D_80082AB4[];

void func_800AE2A4(FuncArg *arg0) {
    s32 field28;
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    field28 = arg0->field28;
    D_800814A0[0] |= 0x8000;
    func_800B1718(field28);
    func_800B1DBC(arg0->field2C);
    D_80082AB4[0] = arg0->field4;
    func_800AE148(arg0);
}
