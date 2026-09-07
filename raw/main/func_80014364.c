#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80023A00(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_8002727C(void *arg0, s32 arg1);
extern s32 func_80027254(void *arg0);
extern void func_80027324(void *arg0, s32 arg1);

extern u8 D_80027DD0[];
extern u8 D_8002B968[];

void *func_80027364(s32 arg0)
{
    u8 *base;
    u8 *work;

    base = D_8002B968;
    work = D_8002B968 + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x68);
        func_8004491C(base, D_80027DD0);
    } else {
        func_80023A00(base);
        FIELD(base, u16, 0x1E) &= 0x7FFF;
        bzero(work, 0x180);
    }

    func_8002727C(work, 4);
    FIELD(base, void *, 0xC) = work + 0xE0;
    FIELD(work, s32, 0xEC) = func_80027254(work + 0xF0);
    func_80027324(work, arg0);
    return base;
}
