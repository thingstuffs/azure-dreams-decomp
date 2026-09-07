#include "common.h"

extern void func_80047784();
extern s32 func_80047D44();
extern void func_80048088();
extern void func_8004827C();
extern void func_80099FDC();
extern void func_8009A21C();
extern s32 func_8009FB34();
extern void func_800A2B04();
extern void func_800A34BC();
extern void func_800A9C80() __attribute__((noreturn));
extern void func_800A9CB4() __attribute__((noreturn));
extern void func_800BC26C();
extern s32 func_800BCB04();

extern u8 D_8006CCF8[];
extern u8 D_80080100[];
extern s32 D_80081488[];
extern s32 D_80083160[];
extern s8 D_800DCF4D[];
extern u8 D_800E8000[];

void func_800A9C18(void *arg0, void *arg1, void *arg2, s32 arg3)
{
    s32 aligned;
    s32 mode;
    register s32 kind ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *base;
    s16 *world;

    base = (u8 *)arg0 + 0x20;
    aligned = arg3 & ~3;
    mode = arg3 & 3;

    if (mode == 2) {
        if ((aligned << 16) == 0) {
            *(s32 *)((u8 *)arg2 + 0x28) =
                func_80047D44(*(u8 *)(base + 0x13));
            func_800A9C80();
        }
        do {
            *(s32 *)((u8 *)arg2 + 0x28) = D_80081488[0];
        } while (0);
        D_800DCF4D[0] = -1;
        func_800A9CB4();
    }

    kind = *(u8 *)(base + 0x13);
    if (kind != 0x38) {
        func_80048088(kind);
    }
    func_8004827C(arg0, *(u8 *)(base + 0x13));

    *(s8 *)((u8 *)arg2 + 0x26) =
        func_8009FB34(*(u8 *)((u8 *)arg2 + 0x24),
                      *(u8 *)((u8 *)arg2 + 0x25));
    func_800A2B04(arg1,
                  *(u8 *)((u8 *)arg2 + 0x24),
                  *(u8 *)((u8 *)arg2 + 0x25));

    *(s16 *)(base + 0x88) =
        func_800BCB04(*(u16 *)((u8 *)arg1 + 2),
                      *(u16 *)((u8 *)arg1 + 6),
                      (s16)(*(u16 *)((u8 *)arg1 + 0xA) - 0x20));

    *(s16 *)((u8 *)arg2 + 0x1E) = 0x1000;
    *(s16 *)((u8 *)arg2 + 0x1C) = 0x1000;
    *(s32 *)((u8 *)arg2 + 0xC) = 0x2C808080;
    *(u16 *)((u8 *)arg2 + 0x14) |= 0x8000;

    world = (s16 *)D_80083160;
    func_80047784(arg2,
                  (*(u8 **)((u8 *)arg2 + 0x2C))[
                      ((world[0x64] + *(s16 *)(base + 0x2A) + 0x100) >> 9) & 7],
                  0);

    func_80099FDC(arg0);
    if ((*(s32 *)(base + 0x14) & 0x4000) == 0) {
        func_800A34BC(base);
    }

    func_8009A21C(*(u8 *)((u8 *)arg2 + 0x24),
                  *(u8 *)((u8 *)arg2 + 0x25),
                  (*(s32 *)(base + 0x1C) & 0x2000) ? 0x300 : 0x3000);

    *(s8 *)(base + 0x71) = 0;
    *(s32 *)(base + 0x1C) |= 0x40000000;
    func_800BC26C(arg0, 0, (u8 *)arg2 + 0x2C, base + 0x2A);

    if (D_8006CCF8[
            ((world[0x64] + *(s16 *)(base + 0x2A) + 0x100) >> 9) & 7] != 0) {
        *(u16 *)((u8 *)arg2 + 0x14) |= 1;
        return;
    }
    *(u16 *)((u8 *)arg2 + 0x14) &= 0xFFFE;
}
