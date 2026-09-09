#include "common.h"

typedef struct {
    u8 pad12[0x12];
    s16 value12;
    u16 value14;
} Func800CF16CArg;

extern s32 func_800D1A80(void *arg0, void *arg1, Func800CF16CArg *arg2, s32 arg3);
extern void func_800A56C0(void);

void func_800D48CC(void *arg0, void *arg1, Func800CF16CArg *arg2, s32 arg3) {
    if (func_800D1A80(arg0, arg1, arg2, arg3) != 0) {
        func_800A56C0();
        return;
    }

    arg2->value12 = 0x7E40;
    arg2->value14 |= 0x100;
}
