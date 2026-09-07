#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80407160(s32 arg0);

extern s32 D_804007A4[];
extern s32 D_804007CC[];

void func_80020830(s32 arg0, s32 arg1) {
    s32 t0;

    t0 = arg0 + 0x20;
    if (arg0 == 0) {
        func_8007C040(D_804007A4, D_804007CC, 0x153);
        func_8007BEF0(1);
        arg0 = 1;
    }
    *(s32 *)(arg0 + 0x44) = arg1;
    func_80407160(t0);
}
