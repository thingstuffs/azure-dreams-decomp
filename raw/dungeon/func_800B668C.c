#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083160[];

void func_800BBDEC(void *arg0, void *arg1, void *arg2)
{
    u8 *scratch = (u8 *)0x1F800000;
    void **global = (void **)D_80083160;
    u8 *prim;
    u32 index;
    s32 primWord;
    s16 y;

    FIELD(scratch, void *, 0x20) = (u8 *)*global + 0xB0;
    FIELD(scratch, s32, 0xE4) = FIELD(arg1, s16, 2);
    FIELD(scratch, s32, 0xE8) = FIELD(arg1, s16, 6);
    FIELD(scratch, s32, 0xEC) = FIELD(arg1, s16, 0xA);
    prim = FIELD(*global, u8 *, 0x8D0);

    func_800649A0();

    FIELD(scratch, u16, 0x100) = FIELD(arg2, u16, 0x16);
    FIELD(scratch, u16, 0x104) = FIELD(arg2, u16, 0x1A);
    FIELD(scratch, u16, 0x102) = FIELD(arg2, u16, 0x18);
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    FIELD(scratch, s16, 0x7C) = 0;
    FIELD(scratch, s16, 0x74) = 0;
    y = -FIELD(arg0, u16, 0x50);
    FIELD(scratch, s16, 0x88) = 0x10;
    FIELD(scratch, s16, 0x78) = 0x10;
    FIELD(scratch, s16, 0x80) = 0;
    FIELD(scratch, s16, 0x70) = 0;
    FIELD(scratch, s16, 0x7A) = 0;
    FIELD(scratch, s16, 0x72) = 0;
    FIELD(scratch, s16, 0x8A) = 0;
    FIELD(scratch, s16, 0x82) = 0;
    FIELD(scratch, s16, 0x8C) = y;
    FIELD(scratch, s16, 0x84) = y;

    index = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          prim + 8, prim + 0x10, prim + 0x18, prim + 0x20,
                          scratch + 0x90, scratch + 0x94);
    FIELD(scratch, u32, 0xC0) = index;

    if (index < 0x1E0U) {
        primWord = FIELD(arg2, s32, 0xC);
        FIELD(prim, s32, 0x14) = 0;
        FIELD(prim, s32, 0x1C) = 0;
        FIELD(prim, s32, 4) = primWord;
        FIELD(prim, u8, 0xC) = FIELD(prim, u8, 4) >> 2;
        FIELD(prim, u8, 0xD) = FIELD(prim, u8, 5) >> 2;
        FIELD(prim, u8, 0xE) = FIELD(prim, u8, 6) >> 2;
        func_80066708(prim);

        if (FIELD(arg2, u16, 0x14) & 4) {
            FIELD(prim, u8, 7) |= 2;
        }

        func_8006658C((u8 *)FIELD(scratch, void *, 0x20) +
                          FIELD(scratch, u32, 0xC0) * 4,
                      prim);
        prim += 0x24;

        if (FIELD(arg2, u16, 0x14) & 4) {
            func_80067F20(prim, 0, 0, 0x20, 0);
            func_8006658C((u8 *)FIELD(scratch, void *, 0x20) +
                              FIELD(scratch, u32, 0xC0) * 4,
                          prim);
            prim += 0xC;
        }
    }

    func_80064A40();
    FIELD(*global, u8 *, 0x8D0) = prim;
}
