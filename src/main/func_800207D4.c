#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);

extern s32 D_804007A4[];
extern s32 D_804007CC[];

extern s32 D_8008DAB4;

void func_800207D4(s32 arg0) {
    u16 t0;
    s32 t1;
    if (arg0 == 0) {
        func_8007C040(D_804007A4, D_804007CC, 0x14B);
        func_8007BEF0(1);
        arg0 = 1;
    }
    t0 = *(u16 *)(arg0 + 0x1E);
    t1 = D_8008DAB4;
    t0 |= 0x8000;
    t1 |= 0x8000;
    *(u16 *)(arg0 + 0x1E) = t0;
    D_8008DAB4 = t1;
}
