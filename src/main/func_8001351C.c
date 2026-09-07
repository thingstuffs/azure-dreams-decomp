#include "common.h"

extern s32 D_80083E98[];
extern s32 D_8002644C[];
extern s32 D_800263C0[];

s32 func_80022138(void);
s32 func_80022160(void);
void func_800264D8(void *arg0);
void func_800265A4(void) __attribute__((noreturn));
void func_80026494(void *arg0);

void func_8002651C(void *arg0) {
    if (D_80083E98[*(s32 *)((s8 *)arg0 + 0x2C) << 5] != 0) {
        *(s32 **)((s8 *)arg0 - 0x10) = D_8002644C;
        func_800265A4();
        return;
    }
    if (func_80022138() >= 3) {
        *(s32 **)((s8 *)arg0 - 0x10) = D_800263C0;
        func_800265A4();
        return;
    }
    if (func_80022160() != 0) {
        func_80026494(arg0);
        func_800265A4();
        return;
    }
    func_800264D8(arg0);
}
