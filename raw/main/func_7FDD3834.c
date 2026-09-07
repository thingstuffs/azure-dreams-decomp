#include "common.h"

typedef struct S_Ctx {
    u8 pad0[0x82C];
    s32 field_82C;
    u8 pad1[0x8D0 - 0x830];
    void *cur;
} S_Ctx;

extern S_Ctx *D_80083160;

extern void func_80066758(void *prim);
extern void func_80066640(void *prim, s32 flag);
extern s16 func_8006649C(s32 a0, s32 a1);
extern s32 func_80066460(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80067F20(void *prim, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_8008A794(void *arg0, void *arg1)
{
    S_Ctx **base;
    s32 low_mask;
    s32 high_mask;
    register s32 outer ASM_REG("$20");
    register s32 row ASM_REG("$21");
    s32 inner;
    s32 row_shift;
    s32 z;
    u16 displacement;
    s32 offset;
    s32 tag;
    register s32 zero ASM_REG("$4");
    void *prim;
    void *prim2;
    void *next;
    S_Ctx *ctx;

    base = &D_80083160;
    low_mask = 0xFFFFFF;
    high_mask = 0xFF000000;

restart:
    outer = 2;
    do {
        row = 0;
        do {
            inner = 1;
            row_shift = row << 8;
            low_mask += inner;
            low_mask -= inner;
            do {
                z = 0x280;
            } while (0);
            low_mask += z;
            low_mask -= z;
            do {
                prim = (*base)->cur;
                (*base)->cur = (u8 *)prim + 0x14;
                *(s32 *)((u8 *)prim + 4) = 0x505050;
                func_80066758(prim);
                func_80066640(prim, 1);
                zero = 0;
                ASM_KEEP(zero);
                tag = inner;
                tag <<= 8;
                tag += outer;
                *(s16 *)((u8 *)prim + 8) = tag;
                displacement = *(u16 *)((u8 *)arg1 + 6);
                *(s16 *)((u8 *)prim + 16) = 0x100;
                *(s16 *)((u8 *)prim + 18) = 0x100;
                *(s16 *)((u8 *)prim + 12) = 0;
                offset = (row_shift - displacement) + outer;
                *(s16 *)((u8 *)prim + 10) = offset;
                *(s16 *)((u8 *)prim + 14) = func_8006649C(zero, 0x1F0);
                *(u32 *)prim = (*(u32 *)prim & high_mask) | ((*base)->field_82C & low_mask);
                *(volatile s32 *)&(*base)->field_82C =
                    ((*base)->field_82C & high_mask) | ((u32)prim & low_mask);

                ctx = *(S_Ctx *volatile *)base;
                prim2 = ctx->cur;
                ctx->cur = (u8 *)prim2 + 0xC;
                func_80067F20(prim2, 0, 0,
                              func_80066460(1, 3, z, row_shift) & 0xFFFF, 0);
                inner -= 1;
                *(u32 *)prim2 = (*(u32 *)prim2 & high_mask) | ((*base)->field_82C & low_mask);
                z -= 0x80;
                (*base)->field_82C = ((*base)->field_82C & high_mask) | ((u32)prim2 & low_mask);
            } while (inner >= 0);
            row += 1;
        } while (row < 2);
        outer -= 1;
    } while (outer >= 0);

    next = *(void **)((u8 *)arg0 - 8);
    if (next != 0) {
        arg0 = (u8 *)next + 0x20;
        arg1 = *(void **)((u8 *)next + 8);
        goto restart;
    }
    return 0;
}
