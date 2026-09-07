#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s32 word[2];
} __attribute__((packed)) Packed8;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void *func_8004DA74(void *, void *, s32);
extern void func_800BC1DC(void *, void *, void *);

extern Packed8 D_8002021C;
extern u8 D_800223D8[8];
extern u8 D_800223E0[8];
extern u8 D_800223E8[8];
extern void *D_80024468;
extern void *D_8002446C;
extern s32 D_80053858[4];
extern s32 D_80053A88;
extern u8 D_800782EC[8];

void func_80022290(void *arg0)
{
    Packed8 local;
    void *obj1;
    void *data1;
    void *obj2;
    void *data2;
    void *tail_value;

    local = D_8002021C;
    func_800BC1DC(&local, D_800223D8,
                  func_8004DA74(arg0, D_8002446C, 0));
    func_800BC1DC((u8 *)&local + 4, D_800223D8, D_800782EC);

    obj1 = func_8003FC64(1);
    if (obj1 != NULL) {
        data1 = obj1 + 0x20;
        FIELD(obj1, void *, 0x10) = D_800223E0;
        func_8004491C(obj1, &D_80053A88);
        FIELD(data1, s16, 0xC) = 0xB8;
        FIELD(data1, s16, 0xE) = 0x14;
        FIELD(data1, s16, 0x10) = 0x7C;
        FIELD(data1, s16, 0x12) = 0x18;
        FIELD(data1, s16, 0x16) = 1;
        FIELD(data1, s32, 8) = 0x402020;
    }

    obj2 = func_8003FC64(1);
    if (obj2 != NULL) {
        data2 = obj2 + 0x20;
        FIELD(obj2, void *, 0x10) = D_800223E8;
        func_8004491C(obj2, D_80053858);
        FIELD(data2, s16, 0x14) = 0xF0;
        FIELD(data2, s16, 0x16) = 0x20;
        FIELD(data2, s16, 0x18) = 3;
        tail_value = D_80024468;
        FIELD(data2, s16, 0x1A) = 0x7C80;
        FIELD(data2, s32, 0x10) = 0x808080;
        FIELD(data2, void *, 4) = tail_value;
    }
}

/* MECHANISM: the true-space ABI preserves incoming arg0; a packed 8-byte local
   produces the lwl/lwr and swl/swr copy, while split object/data names shape s0.
   A one-read tail_value hoists the final global load and removes its delay nop. */
