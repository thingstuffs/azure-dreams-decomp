#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s8 func_8009FB34(u8, u8);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80099FDC(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_800BC26C(void *, s32, void *, void *);

void func_800B22F0(void *arg0, void *arg1, void *arg2)
{
    u8 *state = (u8 *)arg0 + 0x20;

    FIELD(arg2, s8, 0x26) =
        func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    FIELD(state, s16, 0x88) =
        func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                      (s16)(FIELD(arg1, u16, 0xA) - 0x20));

    FIELD(arg2, s16, 0x1E) = 0x1000;
    FIELD(arg2, s16, 0x1C) = 0x1000;
    FIELD(arg2, s32, 0x0C) = 0x2C808080;
    FIELD(arg2, u16, 0x14) |= 0x8000;
    func_80099FDC(arg0);

    func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                  (FIELD(state, u32, 0x1C) & 0x2000) ? 0x300 : 0x3000);

    FIELD(state, u8, 0xAD) = 1;
    FIELD(state, u8, 0x71) = 0;
    FIELD(state, u32, 0x1C) |= 0x40000000;
    func_800BC26C(arg0, 0, (u8 *)arg2 + 0x2C, (u8 *)arg0 + 0x4A);
}
