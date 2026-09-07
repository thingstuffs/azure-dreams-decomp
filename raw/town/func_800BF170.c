#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_8003DB94(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F104(void *, s32, void *);
extern u8 D_80045340[];
extern u8 D_80089634[];
extern u8 D_800BE0D4[];
extern s32 D_800D20E8[];
extern u8 D_800D20F4[];

void func_800BC8D0(void *arg0, s32 arg1, void *arg2)
{
    s32 *data;

    FIELD(arg2, u16, 0x14) |= 0x1C;
    FIELD(arg0, void *, -0x10) = D_800BE0D4;
    FIELD(arg0, s32, 0x50) = 0;
    FIELD(arg0, void *, 0x48) = D_80089634;
    func_8004491C((u8 *)arg0 - 0x20, D_80045340);

    data = D_800D20E8;
    FIELD(arg0, s32, 0xA0) = data[0];
    FIELD(arg0, s32, 0xA4) = data[1];
    FIELD(arg0, s32, 0xA8) = data[2];
    func_8008F104(arg0, arg1, D_800D20F4);
    func_8003DB94(arg2, data[2], 0);
}
