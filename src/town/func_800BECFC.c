#include "common.h"

typedef struct {
    u32 word0;
    u32 word4;
} __attribute__((packed)) Copy8;

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void *func_8004DA74(void *arg0, void *arg1, s32 arg2);
extern void func_8004E9E4(void);
extern void func_800BC1DC(void *arg0, void *arg1, void *arg2);

extern s32 D_80053A88;
extern u8 D_800782EC[8];
extern Copy8 D_8008961C;
extern u8 D_800BC290[8];
extern u8 D_800BC390[8];
extern u8 D_80111FB0[8];

void func_800BC45C(s32 arg0, s32 arg1)
{
    Copy8 local;
    void *obj;
    u8 *base;

    local = D_8008961C;
    func_8004E9E4();
    *(u16 *)&local.word0 += (s32)(arg1 << 16) >> 14;
    func_800BC1DC(&local, D_800BC290,
                  func_8004DA74(D_80111FB0, (void *)arg0, 0));
    func_800BC1DC((u8 *)&local + 4, D_800BC290, D_800782EC);

    obj = func_8003FC64(1);
    if (obj != 0) {
        *(void **)((u8 *)obj + 0x10) = D_800BC390;
        base = (u8 *)obj + 0x20;
        func_8004491C(obj, &D_80053A88);
        *(s16 *)(base + 0xC) = 0x64;
        *(s16 *)(base + 0xE) = 0x34;
        *(s16 *)(base + 0x10) = 0x7C;
        *(s16 *)(base + 0x12) = 0x18;
        *(s16 *)(base + 0x16) = 1;
        *(s32 *)(base + 8) = 0x402020;
        *(s16 *)(base + 2) = 0x1E;
    }
}

/* MECHANISM: A packed 8-byte stack aggregate forces the retail lwl/lwr/swl/swr copy
   and preserves the sibling objects at sp+0x10 and sp+0x14.
   The true no-argument func_8004E9E4 call plus cdk lineage closes base coloring/order. */
