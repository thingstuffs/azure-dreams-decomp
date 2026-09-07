#include "common.h"

extern void func_800478B8(void *arg);
extern void func_80174068(void) __attribute__((noreturn));
extern s32 D_800814A0[3];

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1c;
    u16 field1e;
} Func80DE678C_Obj;

void func_80DE678C(void *arg0, s32 *arg1, Func80DE678C_Obj *arg2) {
    func_800478B8(arg2);
    if (arg2->flags & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80174068();
        return;
    }

    arg2->field1e += 0x200;
    arg2->field1c = arg2->field1e;
    arg1[3] /= 2;
    arg1[4] /= 2;
    arg1[5] -= 20000;
    arg1[0] += arg1[3];
    arg1[1] += arg1[4];
    arg1[2] += arg1[5];
}
