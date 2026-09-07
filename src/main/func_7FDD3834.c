#include "common.h"

typedef struct S_Ctx {
    u8 pad0[0x82C];
    s32 field_82C;
    u8 pad1[0x8D0 - 0x830];
    void *cur;
} S_Ctx;

extern S_Ctx *D_80083160;

extern void func_70066758(void *prim);
extern void func_70066640(void *prim, s32 flag);
extern s16 func_7006649C(s32 a0, s32 a1);
extern s32 func_70066460(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_70067F20(void *prim, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_8008A794(void *arg0, void *arg1)
{
    S_Ctx **base;
    s32 low_mask;
    s32 high_mask;
    s32 outer;
    s32 row;
    s32 inner;
    s32 row_shift;
    s32 z;
    u16 displacement;
    s32 offset;
    void *prim;
    void *prim2;
    void *next;

    base = &D_80083160;
    low_mask = 0xFFFFFF;
    high_mask = 0xFF000000;

restart:
    outer = 2;
outer_loop:
    row = 0;
row_loop:
    inner = 1;
    row_shift = row << 8;
    row_shift += low_mask;
    row_shift -= low_mask;
    z = 0x280;
inner_loop:
    prim = (*base)->cur;
    (*base)->cur = (u8 *)prim + 0x14;
    *(s32 *)((u8 *)prim + 4) = 0x505050;
    func_70066758(prim);
    func_70066640(prim, 1);
    *(s16 *)((u8 *)prim + 8) = (s16)((inner << 8) + outer);
    displacement = *(u16 *)((u8 *)arg1 + 6);
    *(s16 *)((u8 *)prim + 16) = 0x100;
    *(s16 *)((u8 *)prim + 18) = 0x100;
    *(s16 *)((u8 *)prim + 12) = 0;
    offset = (row_shift - displacement) + outer;
    *(s16 *)((u8 *)prim + 10) = offset;
    *(s16 *)((u8 *)prim + 14) = func_7006649C(0, 0x1F0);
    *(u32 *)prim = (*(u32 *)prim & high_mask) | ((*base)->field_82C & low_mask);
    (*base)->field_82C = ((*base)->field_82C & high_mask) | ((u32)prim & low_mask);

    prim2 = (*base)->cur;
    (*base)->cur = (u8 *)prim2 + 0xC;
    func_70067F20(prim2, 0, 0,
                  func_70066460(1, 3, z, row_shift) & 0xFFFF, 0);
    inner -= 1;
    *(u32 *)prim2 = (*(u32 *)prim2 & high_mask) | ((*base)->field_82C & low_mask);
    z -= 0x80;
    (*base)->field_82C = ((*base)->field_82C & high_mask) | ((u32)prim2 & low_mask);
    if (inner >= 0)
        goto inner_loop;
    row += 1;
    if (row < 2)
        goto row_loop;
    outer -= 1;
    if (outer >= 0)
        goto outer_loop;

    next = *(void **)((u8 *)arg0 - 8);
    if (next != 0) {
        arg0 = (u8 *)next + 0x20;
        arg1 = *(void **)((u8 *)next + 8);
        goto restart;
    }
    return 0;
}
