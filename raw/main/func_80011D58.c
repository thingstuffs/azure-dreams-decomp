#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80024EEC(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_80024C70(void *arg0, s32 arg1);
extern s32 func_80024C48(void *arg0);
extern void func_80024D18(void *arg0, s32 arg1);

extern u8 D_80027DD0[];
extern u8 D_8002A990[];

void *func_80024D58(s32 arg0, s32 arg1, s32 arg2)
{
    u8 *base;
    u8 *work;

    base = D_8002A990;
    work = D_8002A990 + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x394);
        func_8004491C(base, D_80027DD0);
    } else {
        func_80024EEC(base);
        FIELD(base, u16, 0x1E) &= 0x7FFF;
        bzero(work, 0xE30);
    }

    FIELD(work, s32, 0x7C) = arg1;
    FIELD(work, s32, 0x80) = arg2;
    func_80024C70(work, 0x15);
    FIELD(base, void *, 0xC) = work + 0xB2C;
    FIELD(work, s32, 0xB38) = func_80024C48(work + 0xB3C);
    func_80024D18(work, arg0);
    FIELD(base, s32, 0x10) = 0;
    return base;
}
