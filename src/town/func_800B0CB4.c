#include "common.h"

typedef struct FuncArg {
    s32 field0;
    s32 field4;
    s32 field8;
} FuncArg;

extern void func_800B03B4(s32 arg0);
extern void func_800B0700(s32 arg0);
extern void func_800B1DBC(s32 arg0);
extern void func_8004E130(void);
extern void func_80093894(void);
extern s32 D_800814A0[];

// Set the high-bit flags and pass the three parameters to their handlers.
void func_800AE414(FuncArg *parameters) {
    s32 firstParameter = parameters->field0;
    ((u16 *)parameters)[-1] |= 0x8000;
    D_800814A0[0] |= 0x8000;
    func_800B03B4(firstParameter);
    func_800B0700(parameters->field4);
    func_800B1DBC(parameters->field8);
    func_8004E130();
    func_80093894();
}
